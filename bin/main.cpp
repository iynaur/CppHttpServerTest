#if 1
#include <iostream>
#include "../server/Server.h"

int main(int argc, char** argv)
{
  server::Server server( 8080 );
  server.start();
  std::cout << "This is just a test" << std::endl;
}

#else
#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define PAGE "HI there!"

struct postStatus {
    bool status;
    char *buff;
};


static int ahc_echo(void * cls,
            struct MHD_Connection * connection,
            const char * url,
            const char * method,
                    const char * version,
            const char * upload_data,
            size_t * upload_data_size,
                    void ** ptr) {
  const char * page = (const char *)cls;
  struct MHD_Response * response;
  int ret;

  struct postStatus *post = NULL;
  post = (struct postStatus*)*ptr;

  if(post == NULL) {
    post = (postStatus*)malloc(sizeof(struct postStatus));
    post->status = false;
    *ptr = post;
  }

  if(!post->status) {
    post->status = true;
    return MHD_YES;
  } else {
    if(*upload_data_size != 0) {
        post->buff = (char*)malloc(*upload_data_size + 1);
        snprintf(post->buff, *upload_data_size,"%s",upload_data);
        *upload_data_size = 0;
        return MHD_YES;
    } else {
        printf("Post data: %s\n",post->buff);
        free(post->buff);
    }
  }

  if(post != NULL)
    free(post);

  response = MHD_create_response_from_buffer (strlen(page),
                                              (void*) page,
                          MHD_RESPMEM_PERSISTENT);
  ret = MHD_queue_response(connection,
               MHD_HTTP_OK,
               response);
  MHD_destroy_response(response);
  return ret;
}

int main(int argc,
     char ** argv) {
  struct MHD_Daemon * d;

  d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
               8080,
               NULL,
               NULL,
               &ahc_echo,
               (void*)PAGE,
               MHD_OPTION_END);
  if (d == NULL)
    return 1;
  sleep(10000);
  MHD_stop_daemon(d);
  return 0;
}
#endif
