#pragma once

void _abort(const char*, const char*, int);
void _abort_msg(const char*, const char*, const char*, int);

#define _assert(exp) { if (!(exp)) _abort(#exp,__FILE__,__LINE__); }
#define _assert_msg(exp, msg) { if (!(exp)) _abort_msg(#exp,msg,__FILE__,__LINE__); }
