#include <fcntl.h>
#include <sys/mman.h>
#include "conduct.h"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct conduct* conduct_create(const char *name, size_t a, size_t c){
  struct conduct *new_conduct;
  int fd;
  //creation du conduit anonyme ou nommé selon name
  if (name == NULL) {
    //creation du conduit
    new_conduct=mmap (NULL,sizeof(struct conduct)+c*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

    //verification de la creation
    if (new_conduct == MAP_FAILED){
      handle_error("new_conduct map failed");
    }

    //creation du tube
    //new_conduct->tube = (char*) &(new_conduct)+sizeof(struct conduct);
  }


  else{
    //ouverture / creation de la file
    fd=open(name,O_RDWR|O_APPEND| O_CREAT,0666);
    if (fd< -1 ){
      close(fd);
      handle_error("open failed");
    }
    //file mise à la bonne taille
    if (ftruncate(fd, sizeof(struct conduct)+c*sizeof(char)) == -1){
      close(fd);
      handle_error("ftruncate failed");
    }
    //creation du conduit
    new_conduct=mmap(NULL,sizeof(struct conduct)+c*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    //new_conduct->tube = (char*) &(new_conduct)+sizeof(struct conduct);
    //creation
  }




  //ecriture des informations dans le conduct_write et initialisation des pointeurs de lecture/ecriture
  new_conduct->full = NOTFULL;
  new_conduct->capacite = c;
  new_conduct->t_atomique = a;
  new_conduct->p_read = 0;
  new_conduct->p_write = 0;


  return new_conduct;
}

struct conduct* conduct_open(const char *name){
  int fd;
  struct conduct* rez;

  fd=open(name,O_RDWR|O_APPEND,0666);
  if (fd< -1 ) {
    handle_error("can't open the file");
  };
  struct stat buf;
  if(fstat(fd,&buf)<0) {
    close(fd);
    handle_error("fstat failed");
  };
  rez=mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0L);
  return rez;
}
