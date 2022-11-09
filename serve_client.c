#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *downtime() {
    for (int i; i<3; i++){
        pthread_mutex_lock(&mutex1);
        Node *temp = root;
        root = balanceTree(root);
        freeSubtree(temp);
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
}

void *ServeClient(char *client) {
    FILE *fp;
    fp = fopen(client, "r");
    char func[100];
    int data[100];
    while (fscanf(fp, "%s %d", func, data) == 1){
        if (func == "addNode"){
            pthread_mutex_lock(&mutex1);
            root = addNode(root, data);
            pthread_mutex_unlock(&mutex1);
            printf("[%s]insertNode <%d>\n", client, data);
        }
        else if (func == "removeNode"){
            pthread_mutex_lock(&mutex1);
            root = removeNode(root, data);
            pthread_mutex_unlock(&mutex1);
            printf("[%s]deleteNodeNode <%d>\n", client, data);
        }
        else if (func == "countNodes"){
            printf("[%s]countNodes = <%d>\n", client, countNodes(root));
        }
        else if (func == "avgSubtree"){
            printf("“[%s]avgSubtree = <%f>\n", client, avgSubtree(root));
        }
    }

}
