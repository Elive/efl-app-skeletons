
#if EINA_VERSION_MINOR < 8
static Eina_Lock           _trash_lock;
# define LOCK_NEW(_l)      eina_lock_new(_l)
# define LOCK_FREE(_l)     eina_lock_free(_l)
# define LOCK_TAKE(_l)     eina_lock_take(_l)
# define LOCK_RELEASE(_l)  eina_lock_release(_l)
#else
static Eina_Spinlock       _trash_lock;
# define LOCK_NEW(_l)      eina_spinlock_new(_l)
# define LOCK_FREE(_l)     eina_spinlock_free(_l)
# define LOCK_TAKE(_l)     eina_spinlock_take(_l)
# define LOCK_RELEASE(_l)  eina_spinlock_release(_l)
#endif

static Eina_Trash       *_objects_trash = NULL;

static void
_trash_init(void)
{
   LOCK_NEW(&_trash_lock);
}

static void
_trash_shutdown(void)
{
   void *data;

   /* lock release/take should not be necessary */
   LOCK_TAKE(&_trash_lock);
   EINA_TRASH_CLEAN(&_objects_trash, data)
      free(data);
   LOCK_RELEASE(&_trash_lock);
   LOCK_FREE(&_trash_lock);
}

static OBJ *
_trash_object_lease(void)
{
   OBJ *obj = NULL;

   LOCK_TAKE(&_trash_lock);
   obj = (OBJ *) eina_trash_pop(&_objects_trash);
   LOCK_RELEASE(&_trash_lock);

   if (obj)
     {
        memset(obj, 0, sizeof(OBJ));
        return obj;
     }
   else
     obj = calloc(1, sizeof(OBJ));

   EINA_LOG_DBG("%p", obj);
   return obj;
}

static void *
_trash_object_release(OBJ *obj)
{
   EINA_LOG_DBG("%p", obj);
   LOCK_TAKE(&_trash_lock);
   eina_trash_push(&_objects_trash, obj);
   LOCK_RELEASE(&_trash_lock);
}

