#ifndef _^CPROJECTNAME^_H_
#define _^CPROJECTNAME^_H_

#include <linux/ioctl.h>

#define DEVICE_NAME "^PROJECTNAME^_dev"

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
