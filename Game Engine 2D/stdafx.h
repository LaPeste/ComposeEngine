// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h" no idea what this is but it throws an error

#include <stdio.h>



// TODO: reference additional headers your program requires here

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> // to enable assert
#include <SFML/Audio.hpp>

//STD libraries
//#include <tchar.h>
#include <map>
#include <iostream>
#include <cassert>
#include <string>

#include "Utils.h"

#if __APPLE__ && __MACH__
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#endif