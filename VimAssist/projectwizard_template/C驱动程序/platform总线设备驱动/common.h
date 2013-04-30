#ifndef _COMMON_H_
#define _COMMON_H_

#define DEVICE_NAME "^PROJECTNAME^_plat_dev"

#define PDEBUG

#ifdef PDEBUG
#define PLOG(fmt,args...) printk(KERN_INFO"^PROJECTNAME^_plat:"fmt,##args)
#else
#define PLOG(fmt,args...) /*do nothing*/
#endif

#endif /* _COMMON_H_ */
