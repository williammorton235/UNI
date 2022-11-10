#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *downtime() {
    for (int i = 0; i<3; i++){
        pthread_mutex_lock(&mutex1);
        printf("down");
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
    while (fscanf(fp, "%s %d", func, &data) != EOF){
        if (!strcmp(func, "addNode")){
            pthread_mutex_lock(&mutex1);
            printf("[%s]insertNode <%d>\n", client, data);
            root = addNode(root, data);
            pthread_mutex_unlock(&mutex1);
        }
        else if (!strcmp(func, "removeNode")){
            pthread_mutex_lock(&mutex1);
            printf("[%s]deleteNodeNode <%d>\n", client, data);
            root = removeNode(root, data);
            pthread_mutex_unlock(&mutex1);
        }
        else if (!strcmp(func, "countNodes")){
            printf("1");
            pthread_mutex_lock(&mutex1);
            printf("[%s]countNodes = <%d>\n", client, countNodes(root));
            pthread_mutex_unlock(&mutex1);
        }
        else if (!strcmp(func, "avgSubtree")){
            printf("2");
            pthread_mutex_lock(&mutex1);
            printf("[%s]avgSubtree = <%f>\n", client, avgSubtree(root));
            pthread_mutex_unlock(&mutex1);
        }
    }
    return NULL;
}
