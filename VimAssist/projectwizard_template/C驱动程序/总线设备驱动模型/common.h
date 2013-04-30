#ifndef _COMMON_H_
#define _COMMON_H_

#define PDEBUG

#ifdef PDEBUG
#define PLOG(fmt,args...) printk(KERN_INFO"^PROJECTNAME^:"fmt,##args)
#else
#define PLOG(fmt,args...) /*do nothing*/
#endif

#endif /* _COMMON_H_ */
