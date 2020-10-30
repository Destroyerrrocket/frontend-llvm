#pragma once
#define TOK(X) X
#define COMB2(X,Y) TOK(X ## Y)
#define COMB(X,Y) COMB2(X, Y)
#define STR(X) #X