// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

/*
** IMPORTANT: _GLIBCXX_USE_CXX11_ABI should be defined as 0 before any
**            standard header inclusion
*/
#define _GLIBCXX_USE_CXX11_ABI 0

#include <stdio.h>
#include <sys/mman.h>
#include <gtest/gtest.h>
#include <unordered_map>
#include <semaphore.h>
#include <exception>

using namespace std;

#include <Isolator5.h>
using namespace Typemock;

#include "windefs.h"

#if defined(__clang__)
#undef NO_CPP_LAMBDA_SUPPORT
#else
#define NO_CPP_LAMBDA_SUPPORT 1
#endif

#include "Address.h"
#include "GPSLocation.h"
#include "ITransport.h"
#include "Person.h"
