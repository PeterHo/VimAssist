#include <stdio.h>
#include "interface.h"

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);//初始化GTK
	InitWindow();//建立窗口
	return 0;
}
