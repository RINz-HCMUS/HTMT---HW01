// HCMUS - He thong may tinh - HW01
// Vo Huu Tuan
// github: RINz-HCMUS

#include <iostream>
#include <string.h>
#include <bitset>

using namespace std;

// A.1 and A.2:
void ConvertSignedIntegerTo2sComplement(){
    int x;
    cout << "Input a signed integer X: ";
    cin >> x;

    int cnt = 0;
    int a[16];
    
    int tmp = x;
    if(tmp < 0) tmp *= (-1);

    // convert to Binary
    while(tmp > 0){
        a[cnt] = (tmp % 2);
        tmp /= 2;
        cnt++;
    }
    for(int i = cnt; i < 16; i++) 
        a[i]  = 0;

    // covert to 2's complement form
    if(x < 0){
    // reverse bits    
        for(int i = 0 ; i < 16; i++)
            a[i] = a[i] * (-1) + 1;
    
    //  bits + 1
        tmp = 0;
        while(true){
            if(a[tmp] == 0){
                a[tmp]++;
                break;
            }
            else{
                a[tmp] = 0;
                tmp++;
            }
            // Over -> break
            if(tmp == 16)
                break;
        }
    }    

    cout << "The binary bit pattern of X(2s complement form): ";

    for(int i = 15; i >= 0; i--)
        cout << a[i];

    cout << endl;
    return;
}

// A3 and A4:
void ConvertSinglePrecisionToBinary(){
    float y;
    
    cout << "Input a single precision Y (floating-point number): ";
    cin >> y;

    bitset<32> binaryPattern(*reinterpret_cast<unsigned int*>(&y));

    cout << "Binary bit pattern of Y: " << binaryPattern << endl;

    return;
}

int ConvertBinaryToDecimal(string s){
    int tmp = 1, num = 0;

    for(int i = s.size() - 1; i >= 0; i--){
        if(s[i] == '1')
            num += tmp;
        
        tmp *= 2;
    }

    return num;
}

float ConvertFractionBinaryToDecimal(string s){
    float tmp = 1, frac = 0;

    for(int i = 0; i < s.size(); i++){
        tmp /= 2;
        if(s[i] == '1')
            frac += tmp;
    }

    return frac;
}

bool check(string Ex, string Si){
    if(ConvertBinaryToDecimal(Ex) == 0 && ConvertFractionBinaryToDecimal(Si) != 0.0){
        cout << "So khong the chuan hoa (Denormalized)" << endl;
        return true;
    }
    
    if(Ex == "11111111"){
        if(ConvertFractionBinaryToDecimal(Si) == 0.0){
            cout << "Infinity!" << endl;
            return true;
        }
        else{
            cout << "NaN - Not a Number" << endl;
            return true;
        }
    }

    return false;
}



void ConvertSinglePrecisionToDecimal(){
    string y;

    cout << "Input a single precision Y (binary bit pattern): ";
    getline(cin, y);

    if(y.size() != 32){
        cout << "Invalid value. Try again!\n";
        return;
    }

    string Signed = "";
    string Exponent = "";
    string Significand = "";
    string integerPart = "1";
    string fractionPart = "";

    Signed = y[0];

    Exponent += y.substr(1, 8);
    int K = 127;
    int E = ConvertBinaryToDecimal(Exponent) - K;
    Significand += y.substr(9, 23);
    
    if(check(Exponent, Significand))
        return;

    int index;
    for(int i = 0; i < Significand.size(); i++)
        if(Significand[i] == '1')
            index = i;
    

    for(int i = 0; i < E; i++)
        integerPart += Significand[i];

    fractionPart += Significand.substr(E, (index - E + 1));
    
    
    float number = ConvertBinaryToDecimal(integerPart) + ConvertFractionBinaryToDecimal(fractionPart);
    if(Signed == "1")
        number *= (-1);
        
    cout << "Signed: " << Signed << endl;
    cout << "Exponent: " << Exponent << endl;
    cout << "Significand: " << Significand << endl; 
    cout << "Fixed point number: " << integerPart << "." << fractionPart << endl;     
    cout << "Decimal value: " << fixed << number << endl;

    return;
}

int main(){
    int x;
    cout << "A. Program to adopt these requirements:\n";
        cout << "-------------------------------------------------------------------------------------\n";
    
    while(true){
        cout << "-------------------------------------------------------------------------------------\n";
        cout << "Press 1 to Convert a signed integer to 2's Complement form.\n";
        cout << "Press 2 to Convert a single precision (floating-point number) to Binary bit pattern.\n";
        cout << "Press 3 to Convert a single precision (binary bit pattern) to floating-point number.\n";
        cout << "Press 0 to Exit\nYour choose: "; 

        cin >> x;
        cin.ignore();
    
        if(x == 1){
            ConvertSignedIntegerTo2sComplement();
            cin.ignore();
        }
        else if(x == 2){
            ConvertSinglePrecisionToBinary();
            cin.ignore();
        }
        
        else if(x == 3){
            ConvertSinglePrecisionToDecimal();
            cin.ignore();
        }
        else if(x == 0){
            break;
        }
        
        else
            cout << "Invalid. Try again!\n";

    }

  return 0;  
} 
