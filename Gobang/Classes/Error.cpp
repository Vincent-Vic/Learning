/******************************************************
> Project Name: Gobang
> Version: 1.0
> File Name: Background.h
> Author: Vincent Vic
> Mail: Vincent-Vic@qq.com
> Created by:  Vincent Vic  on 2018/8/18.
> Functional:  Error element
*******************************************************/
#include "Error.h"

void ResErrHandling(bool respond, string code)
{
	if (respond) {
		String Code = "Error reporting: resource loss or damage ";
		Code.append(code);
		MessageBox(Code.getCString(), "Error alert");
		Director::getInstance()->end();
	}
}
