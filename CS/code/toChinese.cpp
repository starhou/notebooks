#include<vector>
#include<iostream>
#include<algorithm>
#include <string>

    auto subfun(std::string substr, int cnt, bool decimal)
    {
        int n = substr.size(), left = 0, right = n-1, id, base = 4-n;
        std::string res = "";
        std::vector<std::string> num = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
        std::vector<std::string> unit;
        if (decimal == 1) unit = {"角","分","厘",""};
        else unit = {"仟","佰","拾",""};
        
        std::vector<std::string> units = {"","元","万","亿","万亿"};
        //前置0
        while(left<n && substr[left] == '0')  ++left;
        if(left == n) goto stop;
        if(left > 0) res += "零";
        //后置0
        while(right>0 && substr[right] == '0')  --right;


        while (left<=right)
        { 
            if(substr[left] == '0')
            {
                res += "零";
                while (substr[left] == '0')  ++left; 
            }
            else
            {
                id = substr[left]-'0';
                res += num[id];
                res += unit[left+base];
                ++left;
            } 
            
        }
        
        res += units[cnt]; 
        stop:
        return res;
    };


std::string toChinese(std::string str) {
    // write code here
    /*10<substr<10000, 有三位*/
    std::string ans = "";



    int length = str.size()-1, i;
    std::string decimals = "", now;
    int cnt = 0;
    std::vector<std::string> buffer;


    for(;length>=0 && length>=length-4; --length)
    {
        if(str[length] == '.') {str.pop_back(); break;}
        decimals += str[length];
        str.pop_back();
    }
    if(decimals.size()) 
    {
        std::reverse(decimals.begin(),decimals.end());
        while(decimals.size()<4) decimals.push_back(0);
        now = subfun(decimals, cnt, 1);
        buffer.push_back(now);
    }

    cnt = 1;
    while (length>4)
    {
        now = subfun(str.substr(length-4, 4), cnt, 0);
        length -= 4;
        ++cnt;
        buffer.push_back(now);
    }
    
    now = subfun(str.substr(0, length), cnt, 0);
    buffer.push_back(now);
    
    while (buffer.size())
    {
        ans += *(buffer.end()-1);
        buffer.pop_back();
    }
    
    return ans;
}




int main(int argc, char const *argv[])
{
    /* code */

    auto a = toChinese("2002345679.001");
    std::cout<<a<<std::endl;
    return 0;
}

