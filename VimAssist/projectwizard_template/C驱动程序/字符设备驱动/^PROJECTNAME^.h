#ifndef _^CPROJECTNAME^_H_
#define _^CPROJECTNAME^_H_

#include <linux/ioctl.h>

#ifndef ^CPROJECTNAME^_MAJOR
#define ^CPROJECTNAME^_MAJOR 0   /*预设的^PROJECTNAME^的主设备号*/
#endif

#ifndef ^CPROJECTNAME^_NR_DEVS
#define ^CPROJECTNAME^_NR_DEVS 4    /*设备数*/
#endif

#ifndef ^CPROJECTNAME^_SIZE
#define ^CPROJECTNAME^_SIZE 4096
#endif

/*^PROJECTNAME^设备描述结构体*/
struct ^PROJECTNAME^_dev                                     
{                                                        
    bool canRead;
    bool canWrite;
    char *data;                      
    unsigned long size;       
    wait_queue_head_t rwq;
    wait_queue_head_t wwq;
    struct semaphore sem;
};

#define ^CPROJECTNAME^_IOC_MAGIC 'k'

#define ^CPROJECTNAME^_IOCPRINT    _IO(^CPROJECTNAME^_IOC_MAGIC, 1)
#define ^CPROJECTNAME^_IOCGETDATA  _IOR(^CPROJECTNAME^_IOC_MAGIC, 2, int)
#define ^CPROJECTNAME^_IOCSETDATA  _IOW(^CPROJECTNAME^_IOC_MAGIC, 3, int)

#define ^CPROJECTNAME^_IOC_MAXNR   3

#define PDEBUG

#ifdef PDEBUG
#define PLOG(fmt,args...) printk(KERN_INFO"^PROJECTNAME^:"fmt,##args)
#else
#define PLOG(fmt,args...) /*do nothing*/
#endif

#endif /* _^CPROJECTNAME^_H_ */
