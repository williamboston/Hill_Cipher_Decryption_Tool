#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helpers.h"

#define MOD 27

typedef struct char_node node_t;

struct char_node
{
    char ch;
    int index;
    node_t *next;
};


node_t * add_char(node_t * head, char c, int index)
{
	node_t *return_node; 
	node_t *temp;

	return_node = malloc(sizeof (return_node));

	return_node->next = NULL;
	return_node->ch = c;
    return_node->index = index;

	if (head == NULL)
	{
		head = return_node;
	}
	else
	{
		temp = head;
		
		while (temp->next != NULL)
		{	
			temp = temp->next;
		}
		temp->next = return_node;
	}
	return head;
}


void link_to_array(node_t * head, int index, int * int_array)
{
	while(head->next != NULL)
	{
		if (head->index == index)
		{
            char c = head->ch;
            int value = convert_to_int(c);
            *int_array = value;
            break;
		}
		else
		{
			head = head->next;
		}
	}
}

int main(int argc, char **argv)
{

    node_t *cipher_list = NULL;
    int char_counter = 0;

    for (int i=1; i<argc; i++)
    {
        //for each character
        for (int c=0; c<strlen(argv[i]); c++)
        {
            node_t *temp = add_char(cipher_list, argv[i][c], char_counter);
            char_counter++;
            cipher_list = temp;
        }
        
        node_t *space = add_char(cipher_list, ' ', char_counter);
        cipher_list = space;
        char_counter++;
    }

    //array inits
    int *cipher_int_array = malloc(sizeof(int)*char_counter);
    int *plaintext_int_array = malloc(sizeof(int)*char_counter);
    char *plaintext_array = malloc(sizeof(char)*char_counter);


    //for every ciphertext char, convert it to its corresponding int and add to the int array
    for (int c=0; c<char_counter; c++)
    {
        link_to_array(cipher_list, c, &cipher_int_array[c]);
    }

    char ccipher_matrix[4];
    int icipher_matrix[4];
    char cplain_matrix[4];
    int iplain_matrix[4];

    //now ask for suspect bigrams
    //bigram 1
    printf("\nPlease enter suspect ciphertext bigram character 1 _x: ");
    scanf(" %c", &ccipher_matrix[0]);
    printf("Please enter suspect ciphertext bigram character 1 x_: ");
    scanf(" %c", &ccipher_matrix[2]);

    printf("Please enter the corresponding plaintext bigram character 1 _x: ");
    scanf(" %c", &cplain_matrix[0]);
    printf("Please enter the corresponding plaintext bigram character 1 x_: ");
    scanf(" %c", &cplain_matrix[2]);

    //bigram 2
    printf("\nPlease enter suspect ciphertext bigram character 2 _x: ");
    scanf(" %c", &ccipher_matrix[1]);
    printf("Please enter suspect ciphertext bigram character 2 x_: ");
    scanf(" %c", &ccipher_matrix[3]);

    printf("Please enter the corresponding plaintext bigram character 2 _x: ");
    scanf(" %c", &cplain_matrix[1]);
    printf("Please enter the corresponding plaintext bigram character 2 x_: ");
    scanf(" %c", &cplain_matrix[3]);

    printf("\n");

    //convert bigrams to ints
    for (int x=0; x<4; x++)
    {
        icipher_matrix[x] = convert_to_int(ccipher_matrix[x]);
        //printf("%d\n", icipher_matrix[x]);
    }
    for (int y=0; y<4; y++)
    {
        iplain_matrix[y] = convert_to_int(cplain_matrix[y]);
        //printf("%d\n", iplain_matrix[y]);
    }


    /////////////////////////////////////////////////////////////////////
    //STEP 1:
    //find inverse of P
    int inv_P[4];

    inverse_matrix(iplain_matrix, inv_P, MOD);

    ////////////////////////////////////////////////////////////////////////////
    //STEP 2
    //find (supposed) encryption key
    int encryption_key[4];

    encryption_key[0] = modulo_euc(((icipher_matrix[0] * inv_P[0]) + (icipher_matrix[1] * inv_P[2])), MOD);
    encryption_key[1] = modulo_euc(((icipher_matrix[0] * inv_P[1]) + (icipher_matrix[1] * inv_P[3])), MOD);
    encryption_key[2] = modulo_euc(((icipher_matrix[2] * inv_P[0]) + (icipher_matrix[3] * inv_P[2])), MOD);
    encryption_key[3] = modulo_euc(((icipher_matrix[2] * inv_P[1]) + (icipher_matrix[3] * inv_P[3])), MOD);

    ///////////////////////////////////////////////////////////////////////////////
    //STEP 3
    //find inverse of encryption key
    int decryption_K[4];

    inverse_matrix(encryption_key, decryption_K, MOD);

    //////////////////////////////////////////////////////////////////////////////
    //STEP 4
    //vector transform the ciphertext using the decryption key
    for (int z=0; z<char_counter; z+=2)
    {
        //perform vector multiplication
        vector_multiply(decryption_K, cipher_int_array, plaintext_int_array, MOD, z);
    }

    printf("\nYour supposed plaintext based on the given correspondants:\n\n");

    //convert back to chars and print the output
    for (int n=0; n<char_counter; n++)
    {
        plaintext_array[n] = convert_to_char(plaintext_int_array[n]);
        printf("%c", plaintext_array[n]);
    }

    printf("\n\n");

    return 0;
}