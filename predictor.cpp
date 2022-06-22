#include "predictor.h"
#include <sstream>
#include <iomanip>

Predictor::Predictor(unsigned int m, unsigned int n, unsigned int addrLength, bool debug){
    this->historyBits = m; // Size of global history
    this->globalHistory = 0; 
    this->addrBits = addrLength;
    this->debug = debug;
    this->correct = 0;
    this->total = 0;
	this->n_bit = n;
	this->mat.resize(power(addrBits), vector<int>(power(m), 0));    printf("BHT: %u-bit\n", n);
    printf("Address length: %u\n", this->addrBits);
    printf("History length: %u\n", this->historyBits);
    printf("Debug mode: %u\n", this->debug);
};

int Predictor::power(int p){
	int i,result = 1;
	for(i = 0; i < p; i++){
        result = result * 2;
    }
	return result;
	
}

void Predictor::updateGlobalHistory(bool expected){
    globalHistory = globalHistory << 1;
    globalHistory = globalHistory | expected;
    unsigned int mask = (1 << this->historyBits) - 1;
    globalHistory = globalHistory & mask; 
}

bool Predictor::makePrediction(string input, bool expected){
    // Convert Hex address to integer address
    unsigned int address = truncateAddress(hexToInt(input));

    // Currently, this simple branch predictor simulator simply takes 
    // the previous observed branch direction as the next prediction.
    // Predict branch based on last observed branch
    bool predicted;
	
    //predicted = globalHistory & 1; 
	
	
	this->bht_entries.insert({address , globalHistory});
   
    

    // Update statistics
    if (n_bit==1)
	{
		predicted = mat[address][globalHistory];
		if(predicted == expected){
			this->correct++;
		}
		else
		{
			mat[address][globalHistory] = expected;
		}
	}
	else{
		//printf("in 2 bit ");
		switch(mat[address][globalHistory])
		{
			case 0: if (expected){
						mat[address][globalHistory] = 1;}
					else{
						this->correct++;}
					break;
			
			case 1 :
					if (expected){
						mat[address][globalHistory] = 3;}
					else{
						mat[address][globalHistory] = 0;
						this->correct++;}
					break;
					
			case 2 :
					if (expected){
						mat[address][globalHistory] = 3;
						this->correct++;}
					else{
						mat[address][globalHistory] = 0;}
					break;
					
			case 3 :
					if (expected){;
						this->correct++;}
					else{
						mat[address][globalHistory] = 2;}
					break;
					
			default: printf("incorrect value \n");		
		}
	}
	
	// Update global history 
    updateGlobalHistory(expected);
	
    this->total++;

    return predicted;
}

/*
 * Print out branch predictor statistics
 */
void Predictor::printStats(){ 
    printf("------------------------------------------\n"); 
    if(total == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Misclassification rate: %.2f%%\n", 100.00 * (1 - (double)(this->correct)/this->total));
    } 
    
    printf("correct: %d\n", this->correct);
    printf("total: %d\n",this->total);
	
	int bht_c = 0;
	for (auto const &x : this->bht_entries) {
        
		bht_c++;
    }


    // Update the following line to print out the number of BHT entires used.
    printf("BHT used %lu entries\n",bht_c);  
}

/*
 * DO NOT MODIFY BELOW THIS
 */


/*
 * Convert Hex string from trace file to integer address
 */
unsigned int Predictor::hexToInt(string input){
    istringstream converter(input);
    unsigned int result;
    converter >> std::hex >> result; 
    return result;
}

/*
 * Truncate Address to specified number of address bits
 */
unsigned int Predictor::truncateAddress(unsigned int input){
    unsigned int mask = (1 << this->addrBits) - 1;
    unsigned int result = input & mask;

    return result;
}

