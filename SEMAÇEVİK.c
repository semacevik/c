//sema çevik 150112077
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <malloc.h>

DIR* dir;
struct dirent *ent;
FILE* fptr;

typedef struct node2 ReviewNode;

struct node2 {
    int id;
    int length;
    char* text;
    int polarity;
    ReviewNode* next;
};

typedef struct node1 ReviewScoreNode;

struct node1 {
    float scoreNumber;
    int numberOfReviews;
    ReviewNode* reviewList;
    ReviewScoreNode* next;
};

typedef struct {
    ReviewScoreNode* root;
} MasterReviewScoreList;

ReviewScoreNode* searcForScoreNode(MasterReviewScoreList* mml, float score)
{
    ReviewScoreNode* temp;
    temp = mml->root;

    if(temp != NULL)
    {
        if(temp->scoreNumber == score)
            return temp;

        while(temp != NULL)
        {
            if(temp->scoreNumber == score)
                return temp;

            temp = temp->next;
        }
    }

    return temp;
}

ReviewScoreNode* addScoreNode(MasterReviewScoreList*mml, float score)
{
    ReviewScoreNode* newNode;
    newNode = (ReviewNode*)malloc(sizeof(ReviewScoreNode));
    newNode->next = NULL;
    newNode->reviewList = NULL;
    newNode->scoreNumber = score;

    ReviewScoreNode* temp;
    temp = mml->root;

    if(temp == NULL)
        mml->root = newNode;
    else if(temp->scoreNumber > score)
    {
        newNode->next = mml->root;
        mml->root = newNode;
    }
    else
    {
        while(temp != NULL)
        {
            if(temp->next == NULL)
            {
                temp->next = newNode;
                break;
            }
            else if(temp->next->scoreNumber > score)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                break;
            }

            temp = temp->next;
        }
    }

    return newNode;
}

void addReview (ReviewScoreNode* scoreNode, ReviewNode* review)
{
    ReviewNode* temp;
    if(scoreNode->reviewList == NULL)
    {
        scoreNode->reviewList = review;
    }
    else if(scoreNode->reviewList->id > review->id)
    {
        review->next = scoreNode->reviewList;
        scoreNode->reviewList = review;
    }
    else
    {
        temp = scoreNode->reviewList;

        while(temp != NULL)
        {
            if(temp->next == NULL)
            {
                temp->next = review;
                break;
            }
            else if(temp->next->id > review->id)
            {
                review->next = temp;
                temp->next = review;
                break;
            }

            temp = temp->next;
        }
    }

    scoreNode->numberOfReviews += 1;
}

float calculateAverage(MasterReviewScoreList* mml)
{
    float sum = 0;
    int count = 0;

    ReviewScoreNode* root;
    ReviewNode* temp;

    root = mml->root;

    while(root != NULL)
    {
        temp = root->reviewList;

        while(temp != NULL)
        {
            sum += root->scoreNumber;
            count++;

            temp = temp->next;
        }

        root = root->next;
    }

    return sum / count;
}

void showByPolarity(MasterReviewScoreList* mml, int polarity)
{
    ReviewScoreNode* root;
    ReviewNode* temp;

    int count = 0;

    root = mml->root;

    while(root != NULL)
    {
        temp = root->reviewList;

        while(temp != NULL)
        {
            if(temp->polarity == polarity)
            {
                printf("\n\n\tReview id: %d\n", temp->id);
                count++;
            }

            temp = temp->next;
        }

        root = root->next;
    }

    if(count == 0)
        printf("\n\n\tNo reviews with polarity %d", polarity);
    else
        printf("\n\n\tTotal reviews with polarity %d : %d", polarity, count);
}

void showByWord(MasterReviewScoreList* mml, char* word)
{
    ReviewScoreNode* root;
    ReviewNode* temp;
    char* tempWord;

    int count = 0;

    root = mml->root;

    while(root != NULL)
    {
        temp = root->reviewList;

        while(temp != NULL)
        {
            tempWord = strtok(temp->text, " ");

            if(strcmp(tempWord,word) == 0)
            {
                printf("\n\n\tReview id: %d\n", temp->id);
                count++;
            }
            else
            {
                while(tempWord = strtok(0, " "))
                {
                    if(strcmp(tempWord,word) == 0)
                    {
                        printf("\n\n\tReview id: %d\n", temp->id);
                        count++;
                    }
                    break;
                }
            }

            temp = temp->next;
        }

        root = root->next;
    }

    if(count == 0)
        printf("\n\n\tNo reviews with word %s", word);
    else
        printf("\n\n\tTotal reviews with word %s : %d", word, count);
}

void menu()
{
    printf("\n\n1) Add a new review-score\n");
    printf("2) Add a new review into a review-score\n");
    printf("3) Calculate the average of all reviews\n");
    printf("4) Show reviews by polarity\n");
    printf("5) Show reviews by word ");
}

int main(){
    MasterReviewScoreList mml;
    mml.root = NULL;
    ReviewScoreNode* tempScore = NULL;
    ReviewNode* tempReview = NULL;
    FILE* fptr;
    char* temp;
    char buffer[500];
    char reviewText[100000];
    int count;
    int conCount;
    int proCount;
    char fileName[500];
    char directory[50] = {"ReviewsAboutVideoAndTelevisions\\"};
    char path[100];

    if ((dir = opendir ("ReviewsAboutVideoAndTelevisions\\")) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if (!strcmp (ent->d_name, "."))
                continue;
            if (!strcmp (ent->d_name, ".."))
                continue;

            strcpy(fileName,ent->d_name);

            temp = strtok(ent->d_name,"_");

            tempScore = searcForScoreNode(&mml,atof(temp));

            if(tempScore == NULL)
            {
                tempScore = addScoreNode(&mml,atof(temp));
            }

            temp = strtok(0, "_");

            tempReview = (ReviewNode*)malloc(sizeof(ReviewNode));
            tempReview->next = NULL;
            tempReview->id = atoi(temp);

            strcpy(path,directory);
            strcat(path,fileName);

            printf ("%s - read.\n", path);

            fptr = fopen(path, "r");

            proCount = 0;
            conCount = 0;

            while(fscanf(fptr,"%s",buffer))
            {
                if(feof(fptr))
                    break;
                strcat(buffer," ");
                strcat(reviewText,buffer);
                temp = strtok(buffer,":");
                if(strcmp(temp,"Pros") == 0)
                    proCount++;
                if(strcmp(temp,"Cons") == 0)
                    conCount++;
            }

            if(proCount == 1 && conCount == 1)
                tempReview->polarity = 0;
            else if(proCount == 1)
                tempReview->polarity = 1;
            else
                tempReview->polarity = -1;

            fclose(fptr);

            tempReview->text = (char*)malloc(strlen(reviewText) + 1);
            strcpy(tempReview->text, reviewText);

            count = 0;

            int i;
            for(i=0; i<strlen(reviewText); i++)
                if(reviewText[i] == ' ')
                    count++;

            tempReview->length = count;

            addReview(tempScore,tempReview);
        }

        closedir (dir);
    }
    else
    {
        perror ("");
        return EXIT_FAILURE;
    }

    int des;
    float score;
    int id;
    int polarity;

    while(1)
    {
        menu();
        scanf("%d", &des);

        if(des == 1)
        {
            printf("\n\tEnter score-number: ");
            scanf("%f", &score);

            tempScore = searcForScoreNode(&mml,score);

            if(tempScore == NULL)
            {
                tempScore = addScoreNode(&mml,atof(temp));
                printf("\n\tScore added to the list.");
            }
            else
                printf("\n\tThis score already exists.");
        }
        else if(des == 2)
        {
            printf("\n\tEnter score-number: ");
            scanf("%f", &score);

            printf("\n\tEnter id: ");
            scanf("%d", &id);

            printf("\n\tEnter lenght: ");
            scanf("%d", &count);

            printf("\n\tEnter polarity: ");
            scanf("%d", &polarity);

            printf("\n\tEnter text: ");
            scanf("%s", buffer);

            tempReview = (ReviewNode*)malloc(sizeof(ReviewNode));
            tempReview->next = NULL;
            tempReview->id = id;
            tempReview->polarity = polarity;
            tempReview->length = count;
            tempReview->text = (char*)malloc(strlen(buffer) + 1);
            strcpy(tempReview->text, buffer);

            tempScore = searcForScoreNode(&mml,score);

            if(tempScore == NULL)
            {
                printf("\n\tThis score does not exists.");
            }
            else
            {
                addReview(tempScore, tempReview);
                printf("\n\tReview added to score.");
            }
        }
        else if(des == 3)
        {
            score = calculateAverage(&mml);
            printf("\n\tAverage score: %f", score);
        }
        else if(des == 4)
        {
            printf("\n\tEnter polarity (1 for positive, 0 for neutral -1 for bad): ");
            scanf("%d", &polarity);

            showByPolarity(&mml,polarity);
        }

        else if(des == 5)
        {
            printf("\n\tEnter the word: ");
            scanf("%s", buffer);

            showByWord(&mml,buffer);
        }
    }


    return 0;
}
