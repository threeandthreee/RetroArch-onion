#if defined(MIYOOMINI)

#include "miyoo.h"
#include "gfx/video_driver.h"
#include "configuration.h"
#include "runloop.h"
#include "file_path_special.h"

static void show_miyoo_fullscreen_notification(settings_t* settings){
   char msg[80];
   struct retro_message_ext msg_obj = {0};

   msg[0] = '\0';

   snprintf(msg, sizeof(msg), "Aspect: %s. %s.",
      settings->bools.video_dingux_ipu_keep_aspect ? "Original" : "4:3",
      settings->bools.video_scale_integer ? "1x Scale" : "Screen Fill");

   msg_obj.msg      = msg;
   msg_obj.duration = 1000;
   msg_obj.priority = 3;
   msg_obj.level    = RETRO_LOG_INFO;
   msg_obj.target   = RETRO_MESSAGE_TARGET_ALL;
   msg_obj.type     = RETRO_MESSAGE_TYPE_STATUS;
   msg_obj.progress = -1;

   runloop_environment_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &msg_obj);
}

void miyoo_event_fullscreen_impl(settings_t* settings){
   /* Toggle Aspect & Scaling */
   settings->bools.video_dingux_ipu_keep_aspect = !settings->bools.video_dingux_ipu_keep_aspect;
   if (!settings->bools.video_dingux_ipu_keep_aspect) {
      settings->bools.video_scale_integer = !settings->bools.video_scale_integer;
   }

   video_driver_apply_state_changes();

   show_miyoo_fullscreen_notification(settings);
}
#endif
