/*  Panagiotis Christodoulou AM:5501
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100      //megistos pinakas 100x100

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};                 //pinakas me tis 8 pithanes kinisis x
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};                 //pinakas me tis 8 pithanes kinisis y

void pinakas_NxN(int maze[MAX][MAX], int size, float prob) {   //synartisi gia dimiourgia tixaiou lavyrinthou
    for(int i = 0; i < size; i++) {                         //gemisma pinaka me tin pithanotita to kelli na einai FREE OR BLOCKED
        for(int j = 0; j < size; j++) {                     
            maze[i][j] = ((float)rand()/RAND_MAX < prob) ? 1 : 0;       //1:FREE 0:BLOCKED me xrisi tou rand
        }
    }
    
    maze[size-1][0] = 1;  // A kelli einai panta FREE (katw aristera)
    maze[0][size-1] = 1;  // B kelli einai panta FREE (panw deksia)
}

void print_NxN(int maze[MAX][MAX], int size, int start_x, int start_y, 
                int goalX, int goalY, int parentX[MAX][MAX], int parentY[MAX][MAX]) { //function gia to print tou pinaka me teliki diadromi ( * step | # blocked | . free)
    int temp[MAX][MAX];                                     //prosorinos pinakas gia na kanoume copy ton arxiko pinaka
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            temp[i][j] = maze[i][j];                        //antigrafi tou arxikou pinaka ston prosorino
        }
    }
    int x = goalX, y = goalY;                             //dilosi telikis thesis
    if (parentX[goalY][goalX] != 0 || parentY[goalY][goalX] != 0 || (goalX == start_x && goalY == start_y)) {   /// Elenxos an yparxei egkyri diadromi
        while(!(x == start_x && y == start_y)) {                //elenxos an einai sto telos
            temp[y][x] = 2;                                     // 2 = thesi pou vriskete ston pinaka NxN
            int old_x = x;                                      
                x = parentX[y][old_x];                             
            y = parentY[y][old_x];                             
        }
    }
    for(int i = 0; i < size; i++) {                        //ektiposi pinaka ( * step | # blocked | . free)
        for(int j = 0; j < size; j++) {                     
            if(j == start_x && i == start_y){
                 printf("S ");          //arxiki thesi
            }else if(j == goalX && i == goalY){
                printf("G ");        //teliki thesi
            }else if(temp[i][j] == 2){
                printf("* ");          
            }else if(temp[i][j] == 1){
                printf(". ");          
            }else{
                printf("# ");
            }                              
        }
        printf("\n");
    }
}

int ucs(int maze[MAX][MAX], int size, int start_x, int start_y, int goalX, int goalY, int parentX[MAX][MAX], int parentY[MAX][MAX], int cost[MAX][MAX]) {       //UCS
    
    int visited[MAX][MAX] = {0};                            //pinakas gia ta visited kelia
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cost[i][j] = 9999;
        }
    }                              
    int queue_x[MAX*MAX], queue_y[MAX*MAX];                 //pinakes gia tin oura syntetagmenwn
    int front = 0, rear = 0;                                
    queue_x[rear] = start_x;                                
    queue_y[rear++] = start_y;                              
    cost[start_y][start_x] = 0;                             
    
    int count = 0;           
    
    while(front < rear) {                                   //oso yparxoun komvoi stin oura
        int best = front;                                   
        for(int i = front; i < rear; i++){
            if(cost[queue_y[i]][queue_x[i]] < cost[queue_y[best]][queue_x[best]]){       //vriskei ton komvo me to xamilotero kostos
                best = i;                                                   
            }                               
        }
        int tempX = queue_x[front],tempY = queue_y[front];       //prosorines metavlites gia antallagi
        queue_x[front] = queue_x[best]; 
        queue_y[front] = queue_y[best]; 
        queue_x[best] = tempX; 
        queue_y[best] =tempY;            
        int x = queue_x[front];
        int y = queue_y[front++];
        if(visited[y][x]){      //if visited sinexise
            continue;
        }                         
        visited[y][x] = 1;                                  //simaiosi tou komvou oti einai visited
        count++;                                           
        
        if(x == goalX && y == goalY) 
            return count;        //an ftasame ston stoxo, epistrepse ton metriti
        
        for(int i = 0; i < 8; i++) {                        
            int newX = x + dx[i], newY = y + dy[i];             //ypologismos neas thesis
            
            if(newX >= 0 && newX < size && newY >= 0 && newY < size && 
               maze[newY][newX] == 1 && !visited[newY][newX]) {     //elenxos an i kinisi einai valid
                int new_cost = cost[y][x] + 1;                      //ypologismos neou kostous
                if(new_cost < cost[newY][newX]) {                   //if neo kostos einai xamilotero
                    cost[newY][newX] = new_cost;                
                    parentX[newY][newX] = x;                        
                    parentY[newY][newX] = y;                        
                    queue_x[rear] = newX;                     
                    queue_y[rear++] = newY;                   
                }
            }
        }
        
        if(x == 0 && y == size-1) {                         //elenxos an vriskomaste sto A
            int newX = size-1;
            int newY = 0;                        
            if(!visited[newY][newX]) {                          
                int new_cost = cost[y][x] + 2;                     //cost me teleport
                if(new_cost < cost[newY][newX]) {               
                    cost[newY][newX] = new_cost;                
                    parentX[newY][newX] = x;                   
                    parentY[newY][newX] = y;                   
                    queue_x[rear] = newX;                     
                    queue_y[rear++] = newY;                   
                }
            }
        }
        else if(x == size-1 && y == 0) {                    //to idio me to panw apla antistrofa
            int newX = 0, newY = size-1;                        
            if(!visited[newY][newX]) {                          
                int new_cost = cost[y][x] + 2;              
                if(new_cost < cost[newY][newX]) {              
                    cost[newY][newX] = new_cost;                
                    parentX[newY][newX] = x;                   
                    parentY[newY][newX] = y;                   
                    queue_x[rear] = newX;                     
                    queue_y[rear++] = newY;                  
                }
            }
        }
    }
    
    return -1;                                       //epistrofi an den vrethike diadromi
}

int astar(int maze[MAX][MAX], int size, int start_x, int start_y, int goalX, int goalY, int parentX[MAX][MAX], int parentY[MAX][MAX], int cost[MAX][MAX]) {      //A* Search
    
    int visited[MAX][MAX] = {0};                            //pinakas gia ta visited kelia
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cost[i][j] = 9999;                              
        }
    }
    int queue_x[MAX*MAX], queue_y[MAX*MAX];                 //lines 148-155 idies me ucs
    int front = 0, rear = 0;                               
    
    queue_x[rear] = start_x;                                
    queue_y[rear++] = start_y;                              
    cost[start_y][start_x] = 0;                            
    int count = 0;                                          
    while(front < rear) {                                   //oso yparxoun komvoi stin oura
        int best = front;                                   
        for(int i = front; i < rear; i++) {                 //psaxnei ton komvo me to xamilotero f=g+h
            int x = queue_x[i];
            int y = queue_y[i];             
            int f = cost[y][x] + abs(x - goalX) + abs(y - goalY); //f=g+h
            
            int bestX = queue_x[best];
            int bestY = queue_y[best];     //syntetagmenes tou trexontos kalyterou komvou
            int bestF = cost[bestY][bestX] + abs(bestX - goalX) + abs(bestY - goalY); //f=g+h
            
            if(f < bestF){
                best = i;
            }                            
        }
        
        int tempX = queue_x[front];
        int tempY = queue_y[front];       
        queue_x[front] = queue_x[best]; 
        queue_y[front] = queue_y[best]; //antallagi tou kalyterou komvou stin arxi
        queue_x[best] = tempX; 
        queue_y[best] = tempY;            
        int x = queue_x[front];
        int y = queue_y[front++];       
        
        if(visited[y][x]){          //idio me ucs
             continue;                        
        }
        visited[y][x] = 1;                               
        count++;                                      
        
        if(x == goalX && y == goalY){
            return count;        //an ftasame ston stoxo
        }         
        
        for(int i = 0; i < 8; i++) {                        //dokimase tis 8 katefthynseis
            int newX = x + dx[i];
            int newY = y + dy[i];             
            
            if(newX >= 0 && newX < size && newY >= 0 && newY < size && 
               maze[newY][newX] == 1 && !visited[newY][newX]) {     //elenxos an i kinisi einai egkyri
                int new_cost = cost[y][x] + 1;              
                if(new_cost < cost[newY][newX]) {               
                    cost[newY][newX] = new_cost;               
                    parentX[newY][newX] = x;                   
                    parentY[newY][newX] = y;                   
                    queue_x[rear] = newX;                    
                    queue_y[rear++] = newY;                  
                }
            }
        }
        
        if(x == 0 && y == size-1) {                         //elenxos an vriskomaste sto A
            int newX = size-1;
            int newY = 0;                        
            if(!visited[newY][newX]) {                          
                int new_cost = cost[y][x] + 2;                     //cost me teleport
                if(new_cost < cost[newY][newX]) {               
                    cost[newY][newX] = new_cost;                
                    parentX[newY][newX] = x;                   
                    parentY[newY][newX] = y;                   
                    queue_x[rear] = newX;                     
                    queue_y[rear++] = newY;                   
                }
            }
        }
        else if(x == size-1 && y == 0) {                    //to idio me to panw apla antistrofa
            int newX = 0, newY = size-1;                        
            if(!visited[newY][newX]) {                          
                int new_cost = cost[y][x] + 2;              
                if(new_cost < cost[newY][newX]) {              
                    cost[newY][newX] = new_cost;                
                    parentX[newY][newX] = x;                   
                    parentY[newY][newX] = y;                   
                    queue_x[rear] = newX;                     
                    queue_y[rear++] = newY;                  
                }
            }
        }
    }
    return -1;                                       //epistrofi an den vrethike diadromi
}

int main() {                                            
    int maze[MAX][MAX];                                 //dilosi tou pinaka lavyrinthou
    int parentX_ucs[MAX][MAX];                              //pinakes gia UCS
    int parentY_ucs[MAX][MAX];
    int cost_ucs[MAX][MAX];  
    //pinakes gia A*
    int parentX_astar[MAX][MAX];
    int parentY_astar[MAX][MAX];
    int cost_astar[MAX][MAX];

    int size, start_x, start_y, goalX, goalY;         
    float prob;                                        
    srand(time(NULL));                                  //arxikopoiisi tou rand me xrono 
    printf("Enter maze size: ");                        
    scanf("%d", &size);                                 
    printf("Enter probability (0-1): ");               
    scanf("%f", &prob);                               
    
    pinakas_NxN(maze, size, prob);                        
    
    printf("Enter start (x y): ");                      
    scanf("%d %d", &start_x, &start_y);                 
    printf("Enter goal (x y): ");                       
    scanf("%d %d", &goalX, &goalY);                  
    
    maze[start_y][start_x] = maze[goalY][goalX] = 1;  //vazoume tin arxi kai ton stoxo os eleuthera

    int ucs_expansions = ucs(maze, size, start_x, start_y, goalX, goalY, parentX_ucs, parentY_ucs, cost_ucs); 
    if (ucs_expansions == -1) {
        print_NxN(maze, size, start_x, start_y, goalX, goalY, parentX_ucs, parentY_ucs);
        printf("No path found\n");
        return 0;  // Termatismos programmatos an den vrethike diadromi
    }
    printf("\n--- Uniform Cost Search ---\n");          
    print_NxN(maze, size, start_x, start_y, goalX, goalY, parentX_ucs, parentY_ucs);
    printf("Cost: %d\nExpansions: %d\n", cost_ucs[goalY][goalX], ucs_expansions);
    
    printf("\n--- A* Search ---\n");                    
    int astar_expansions = astar(maze, size, start_x, start_y, goalX, goalY, parentX_astar, parentY_astar, cost_astar); 
    print_NxN(maze, size, start_x, start_y, goalX, goalY, parentX_astar, parentY_astar); 
    printf("Cost: %d\nExpansions: %d\n", cost_astar[goalY][goalX], astar_expansions); 
    
    return 0;                                           //telos tou programmatos
}