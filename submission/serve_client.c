#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *downtime() {
    for (int i = 0; i<3; i++){
        pthread_mutex_lock(&mutex1);
        Node *temp = root;
        root = balanceTree(root);
        freeSubtree(temp);
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
    return NULL;
}

void *ServeClient(char *client) {
    FILE *fp;
    fp = fopen(client, "r");
    char func[100];
    int data;
    char *token;
    char str[strlen(client)];
    strcpy(str, client);
    token = strtok(str, "_");
    
    while (fscanf(fp, "%s %d", func, &data) != EOF){
        if (!strcmp(func, "addNode")){
            pthread_mutex_lock(&mutex1);
            printf("%sinsertNode %d\n", token, data);
            root = addNode(root, data);
            pthread_mutex_unlock(&mutex1);
        }
        else if (!strcmp(func, "removeNode")){
            pthread_mutex_lock(&mutex1);
            printf("%sdeleteNodeNode %d\n", token, data);
            root = removeNode(root, data);
            pthread_mutex_unlock(&mutex1);
        }
        else if (!strcmp(func, "countNodes")){
            printf("%scountNodes = %d\n", token, countNodes(root));
        }
        else if (!strcmp(func, "avgSubtree")){
            printf("%savgSubtree = %f\n", token, avgSubtree(root));
        }
    }
    fclose(fp);
    return NULL;
}
