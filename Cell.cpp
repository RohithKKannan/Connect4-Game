#include "connect.h"
using namespace std;
Cell::Cell()
{
    token = Empty;
}
Token Cell::GetToken()
{
    return token;
}
void Cell::SetToken(Token token)
{
    this->token = token;
}