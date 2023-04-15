#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{

	struct RecordType** records;
    int size;

};

// Compute the hash function
int hash(int x, int h)
{
	return (x % h);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}
void recordin (struct RecordType* r, struct HashType* h)
{

    int n = hash(r->id, h->size);

    if (h->records[n] == NULL)
    {

        h->records[n] = r;
    }
    else
    {

        printf("collided at index %d\n", n);

    }

}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{

	int i;
	struct RecordType *r;

	for (i=0;i<hashSz;++i)
	{

        r = pHashArray->records[i];

        if (r != NULL)
        {

            printf("index %d -> %d %c %d\n", i, r->id, r->name, r->order);

        }

    }

}

int main(void)
{

	struct RecordType *pRecords;
    int recordSz = 0;
    struct RecordType *r;
    struct HashType t;
	int i;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    t.size = recordSz;
    t.records = (struct RecordType**) malloc(sizeof(struct RecordType*) * t.size);

    if (t.records == NULL)
    {

        printf("unable to allocate memmory\n");
        exit(-1);

    }
    for (i = 0; i < t.size; ++i)
    {

        t.records[i] = NULL;

    }
	for (i = 0; i < recordSz; ++i)
    {

        r = pRecords + i;
        recordin(r, &t);

    }

    displayRecordsInHash(&t,t.size);

    
    for (i = 0; i < recordSz; ++i)
    {

        r = pRecords + i;
        free(r);

    }

    free(t.records);
    free(pRecords);

    return 0;

}
