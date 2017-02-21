#pragma once

#include<battle.h>

void SaveModuleToFile(const char * filename, Module * target, int format);
Module * LoadModuleFromFile(const char * filename);