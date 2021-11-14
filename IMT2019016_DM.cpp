#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;


//CONVERSION FUNCTION FOR CONVERTING HEXADECIMAL TO BINARY

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
    while(getline(file, word))
    {
        //READING EACH LINE AND THEN SEPARATING THEM ABOUT " " SO THAT s/l HEXADECIMAL and NUMBER ARE SEPARATED	
    	vector <string> tokens; 
        stringstream check1(word); 
        string intermediate; 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        }


        //NOW SEPARATING THEM ABOUT 'x' SO THAT WE HAVE JUST THE HEXADECIMAL VALUE NOT 0x
        vector <string> tokens2; 
        stringstream check2(tokens[1]); 
        string intermediate2; 
        while(getline(check2, intermediate2, 'x')) 
        { 
            tokens2.push_back(intermediate2); 
        }





        nums.push_back(tokens2[1]);

    }
    //CREATING AN ARRAY OF SIZE 65536 FOR VALID BITS AND INITIALIZING THEM TO 0
    int validBit[65536] = {0};
    //INITIALIZING 65536 VECTOR OF STRING 
    vector<string> tagBit= vector<string>(65536, " ");
    for(int i=0;i<nums.size(); i++)
    {
    	string bin = HexToBin(nums[i]);
    	string ind;
    	for(int j = 14; j<30; j++)
    	{
    		ind[j-14] = bin[j];
    	}
    	int index = stoi(ind,0,2);
    // IF VALID BIT AT INDEX IS 0 THEN IT IS EMPTY , WE WILL PUT THE TAG VALUE IN THIS CASE 
    	if(validBit[index]==0)
    	{
    		miss++;
    		validBit[index] = 1;
    		string temp;
    		for(int j=0; j<14; j++)
    		{
    			temp = temp+bin[j];
    		}

    		tagBit[index] = temp;
    	}

    	//IF THE VALID BIT IS  THEN TWO CASES
    	else if(validBit[index]==1)
    	{

    		// IF THE 14 TAG BITS MATCHED  THEN WE COUNT IT AS A HIT
    		int count  = 0;
    		for(int j=0; j<14; j++)
    		{
    			if(tagBit[index][j] == bin[j])
    			{
    				count++;
    			}
    		}
    		if(count==14)
    		{
    			hit++;
    		}
    		// IF THE TAG DOESNT MATCH THEN WE COUNT IT AS A MISS AND WE SET THE NEW VALUE AT TAGBIT FIELD AT THIS INDEX
    		else
    		{
    			string temp;
    			for(int j=0; j<14; j++)
    			{
    				temp = temp + bin[j];
    			}
    			tagBit[index] = temp;
    			miss++;
    		}

    	}
    }
    cout<<"HITS = "<<hit<<endl;
    cout<<"MISS = "<<miss;
    


   

}