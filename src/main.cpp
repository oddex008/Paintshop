//
//  main.cpp
//
//  Created by CSCI3081W Guru on 1/15/15.
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//


#include "PaintShop.h"
#include "ColorData.h"

int main(int argc, char* argv[])
{
	PaintShop *app = new PaintShop(argc, argv,800,800, ColorData(1,1,0.95));
	app->runMainLoop();
	exit(0);
}
