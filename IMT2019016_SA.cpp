#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

//CONVERSION FUNCTION TO CONVERT HEXADECIMAL TO BINARY
string HexToBin(string hexdec)
{
    long int i = 0;
    string s;
 
    while (hexdec[i]) 
    {
 
        switch (hexdec[i]) {
        case '0':
            s = s + "0000";
            break;
        case '1':
            s = s + "0001";
            break;
        case '2':
            s = s + "0010";
            break;
        case '3':
            s = s + "0011";
            break;
        case '4':
            s = s + "0100";
            break;
        case '5':
            s = s + "0101";
            break;
        case '6':
            s = s + "0110";
            break;
        case '7':
            s = s + "0111";
            break;
        case '8':
            s = s + "1000";
            break;
        case '9':
            s = s + "1001";
            break;
        case 'A':
        case 'a':
            s = s + "1010";
            break;
        case 'B':
        case 'b':
            s = s + "1011";
            break;
        case 'C':
        case 'c':
            s = s + "1100";
            break;
        case 'D':
        case 'd':
            s = s + "1101";
            break;
        case 'E':
        case 'e':
            s = s + "1110";
            break;
        case 'F':
        case 'f':
            s = s + "1111";
            break;
        }
        i++;
    }


    return s;
}



int main ()
{
    long long int miss = 0;
    long long int hit = 0;
    ifstream file;
    vector<string> nums;
    char filename[50];
    cout<<"Enter file name : ";
    cin>>filename;
    file.open (filename);
    if(!file.is_open())
    {
        cout<<"Error opening the file";
        exit(1);
    }
    string word;

    //SEPARATING ABOUT SPACE AND THEN ABOUT X SO THAT WE JUST HAVE THE HEXADECIMAL ADDRESS
    while(getline(file, word))
    {
        vector <string> tokens; 
        stringstream check1(word); 
        string intermediate; 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        }



        vector <string> tokens2; 
        stringstream check2(tokens[1]); 
        string intermediate2; 
        while(getline(check2, intermediate2, 'x')) 
        { 
            tokens2.push_back(intermediate2); 
        }





        nums.push_back(tokens2[1]);

    }
    //4 ARRAYS INITIALIZED TO 0 EACH REPRESENTING VALID BIT VALUE FOR CORRESSPONDING WAY

    int validBit1[16384] = {0};
    int validBit2[16384] = {0};
    int validBit3[16384] = {0};
    int validBit4[16384] = {0};

    //4 VECTORS INITIALIZED TO EMPTY STRING EACH REPRESENTING TAGBIT VALUE FOR CORRESSPONDING WAY
    vector<string> tagBit1= vector<string>(16384, " ");
    vector<string> tagBit2= vector<string>(16384, " ");
    vector<string> tagBit3= vector<string>(16384, " ");
    vector<string> tagBit4= vector<string>(16384, " ");

    //VECTOR OF VECTORS REPRESENTING STACK..... stack[i] REPRESENTS STACK FOR ith INDEX 
    vector<vector<int>> stack(16384, vector<int>(0));
    for(int i=0;i<nums.size(); i++)
    {
        string bin = HexToBin(nums[i]);
        string ind;
        for(int j = 16; j<30; j++)
        {
            ind[j-16] = bin[j];
        }
        int index = stoi(ind,0,2);


        //IF VALID BIT FOR WAY1 IS 0 THEN WE PUT THE TAGBIT IN WAY1 AND COUNT IT AS A MISS
        if(validBit1[index]==0)
        {
            miss++;
            validBit1[index]=1;
            string temp;
            for(int j=0; j<16; j++)
            {
                temp = temp+bin[j];
            }

            tagBit1[index] = temp;
            stack[index].push_back(1);


        }
        //IF THE TAG BIT IS 1 THEN TWO CASES
        else if(validBit1[index]==1)
        {

        	//IF THE 16 TAGBITS MATCH THEN WE COUNT IT AS A HIT
            int count  = 0;
            for(int j=0; j<16; j++)
            {
                if(tagBit1[index][j] == bin[j])
                {
                    count++;
                }
            }
            if(count==16)
            {
                hit++;
                stack[index].push_back(1);
            }
            //IF THE BITS DONT MATCH THEN WE CHECK WHETHER THE VALID BIT OF WAY 2 IS 0 OR NOT
            else
            {
            	//IF IT IS 0 THEN WE COUNT IT AS A MISS AND PUT IT IN WAY 2

                if(validBit2[index]==0)
                {
                    miss++;
                    validBit2[index]=1;
                    string temp;
                    for(int j=0; j<16; j++)
                    {
                        temp = temp+bin[j];
                    }

                    tagBit2[index] = temp;
                    stack[index].push_back(2);


                }
                //IF IT IS 1 THEN TWO CASES...AND SO ON
                else if(validBit2[index]==1)
                {
                    int count  = 0;
                    for(int j=0; j<16; j++)
                    {
                        if(tagBit2[index][j] == bin[j])
                        {
                            count++;
                        }
                    }
                    if(count==16)
                    {
                        hit++;
                        stack[index].push_back(2);
                    }
                    else
                    {

                        if(validBit3[index]==0)
                        {
                            miss++;
                            validBit3[index]=1;
                            string temp;
                            for(int j=0; j<16; j++)
                            {
                                temp = temp+bin[j];
                            }

                            tagBit3[index] = temp;
                            stack[index].push_back(3);


                        }
                        else if(validBit3[index]==1)
                        {
                            int count  = 0;
                            for(int j=0; j<16; j++)
                            {
                                if(tagBit3[index][j] == bin[j])
                                {
                                    count++;
                                }
                            }
                            if(count==16)
                            {
                                hit++;
                                stack[index].push_back(3);
                            }
                            else
                            {
                                if(validBit4[index]==0)
                                {
                                    miss++;
                                    validBit4[index]=1;
                                    string temp;
                                    for(int j=0; j<16; j++)
                                    {
                                        temp = temp+bin[j];
                                    }

                                    tagBit4[index] = temp;
                                    stack[index].push_back(4);


                                }
                                else if(validBit4[index]==1)
                                {
                                    int count  = 0;
                                    for(int j=0; j<16; j++)
                                    {
                                        if(tagBit4[index][j] == bin[j])
                                        {
                                            count++;
                                        }
                                    }
                                    if(count==16)
                                    {
                                        hit++;
                                        stack[index].push_back(4);
                                    }
                                    //NOW IF ALL THE WAYS ARE FULL AND IT HASNT MATCHED WITH ANY OF THE WAY..THEN WE REPLACE USING THE LRU POLICY
                                    else
                                    {

                                        int count1 = 0;
                                        int count2 = 0;
                                        int count3 = 0;
                                        int count4 = 0;
                                        int c = 0;
                                        int i= stack[index].size() - 1;
                                        //WE CHECK WHICH 3 NUMBERS ARE MOST RECENTLY USED
                                        while(c<3 && i>=0)
                                        {
                                            if(stack[index][i]==4)
                                            {
                                                count4 = 1;

                                            }
                                            if(stack[index][i]==3)
                                            {
                                                count3 = 1;
                                                
                                            }
                                            if(stack[index][i]==2)
                                            {
                                                count2 = 1;
                                                
                                            }
                                            if(stack[index][i]==1)
                                            {
                                                count1 = 1;
                                                
                                            }   

                                            c = count1 + count2  + count3 + count4;
                                            i--;
                                            
                                        }
                                        //WHICHEVER WAS LEAST RECENTLY USED WE PUT IT IN THAT WAY
                                        if(count1==0)
                                        {
                                            miss++;
                                            string temp;
                                            for(int j=0; j<16; j++)
                                            {
                                                temp = temp+bin[j];
                                            }

                                            tagBit1[index] = temp;
                                            stack[index].push_back(1);

                                        }
                                        if(count2==0)
                                        {
                                            miss++;
                                            string temp;
                                            for(int j=0; j<16; j++)
                                            {
                                                temp = temp+bin[j];
                                            }

                                            tagBit2[index] = temp;
                                            stack[index].push_back(2);

                                        }
                                        if(count3==0)
                                        {
                                            miss++;
                                            string temp;
                                            for(int j=0; j<16; j++)
                                            {
                                                temp = temp+bin[j];
                                            }

                                            tagBit3[index] = temp;
                                            stack[index].push_back(3);

                                        }
                                        if(count4==0)
                                        {
                                            miss++;
                                            string temp;
                                            for(int j=0; j<16; j++)
                                            {
                                                temp = temp+bin[j];
                                            }

                                            tagBit4[index] = temp;
                                            stack[index].push_back(4);

                                        }                                                                                

                

                                    }
                                }



                            }
                        }





                    }
                }




            }
        }

    }


    cout<<"HITS = "<<hit<<endl;
    cout<<"MISS = "<<miss;

}




