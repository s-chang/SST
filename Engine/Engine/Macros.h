/**
Written by:  Smyth Chang

Description:  The Macros header is used to define macros for use across multiple files
*/

#pragma once

#define SAFE_RELEASE(x) if(x){x->Release(); x = nullptr;}
#define SAFE_RELEASE2(x) if(x){x->release(); x = nullptr;}