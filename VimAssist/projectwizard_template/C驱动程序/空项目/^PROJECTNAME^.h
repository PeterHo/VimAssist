#ifndef _^CPROJECTNAME^_H_
#define _^CPROJECTNAME^_H_

#define PDEBUG

#ifdef PDEBUG
#define PLOG(fmt,args...) printk(KERN_INFO"^PROJECTNAME^:"fmt,##args)
#else
#define PLOG(fmt,args...) /*do nothing*/
#endif

#endif /* _^CPROJECTNAME^_H_ */
