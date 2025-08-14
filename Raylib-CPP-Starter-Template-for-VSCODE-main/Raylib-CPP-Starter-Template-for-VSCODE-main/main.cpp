#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

//j'ai pris ça comme source https://www.youtube.com/watch?v=VLJlTaFvHo4

//classe balle
class Ball{
    public:
    
    //position de la balle sur l'axe des y
    float x, y;
    
    //vitesse de la balle 
    int speed_x;
    int speed_y;
    
    //rayon de la balle
    int radius;

    // fonction pour dessiner la balle sur le carcle
    void Draw (){
        DrawCircle(x, y, radius, WHITE);
    };

    //fonction pour mettre ä jour les données
    void Update(){
        
        //déplacement de la balle sur l'axe des x
        x += speed_x;
        //déplacement de la balle sur l'axe des Y
        y += speed_y;
    
        //si le bord du ballon dépase l'écran sur l'axe de x, on inverse la vitesse 
        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        }

        //si le bord du ballon dépase l'écran sur l'axe de y, on inverse la vitesse
        if(y - radius <= 0){
            speed_y *= -1;
        }

    }
};

//classe pour le paddle
class Paddle{

    public:
    
    //position du paddle
    float x, y;
    //longueur et hauteur du paddle
    float width, height;
    //vitesse du paddle
    int speed;
    
    void Draw(){
        //dessiner le paddle
        DrawRectangle(x, y, width, height, WHITE);
    }

    //mettre à jour les données du paddle    
    void Update(){
        //si on maintient la flèche de gauche et qu'on est dans la limite de l'écran, le paddle se déplace à gauche (sur l'axe des x, +5)
        if(IsKeyDown(KEY_LEFT)){
            if(x > 0)
                x -= speed; 
        }
        //si on maintient la flèche de droite et qu'on est dans la limite de l'écran, le paddle se déplace à droite (sur l'axe des x, +5)
        else if(IsKeyDown(KEY_RIGHT)){
            if(x < 800-120)
                x += speed; 
        }
    }
};

//classe pour la brique
class Brick{
    public:
    
    //position de la brique
    float x, y;
    //longueur, largeur de la brique
    float width, height;
    
    //fonction pour dessiner la brique
    void Draw(){
        DrawRectangle(x, y, width, height, RED);
    }

};


//initialisation du compteur (variable globale)
int compteur = 0;

//instance de la classe Ball
Ball ball;

//instance de la classe Paddle
Paddle paddle;

//instance de la classe brique
Brick brick;

//fonction pour générer une des nombresà virgules aléatoires (fonction prise de Chatgpt)
float GetRandomFloat(float min, float max) {
    return min + static_cast<float>(GetRandomValue(10, 10000)) / 10000.0f * (max - min);
}

//fonction pour la fin du jeu (lorsque la balle tombe en bas)
void GameOver(){
    
    //l'utilisateur peut plus bouger le paddle et la balle s'arrête
    ball.speed_x = 0;
    ball.speed_y = 0;
    paddle.speed = 0;

    //affichage de la fin et des options proposées
    DrawText("GAME OVER", GetScreenWidth()/2-150, GetScreenHeight()/2-25, 50, BLACK);
    DrawText("Press ENTER to restart", GetScreenWidth()/2-140, GetScreenHeight()/2+40, 20, BLACK);
    DrawText("Press ESC to exit", GetScreenWidth()/2-140, GetScreenHeight()/2+60, 20, BLACK);

    // si l'utilisateur appuit sur Enter, le jeu recommence, s'il appuit sur Esc, on arrête le programme
    if(IsKeyPressed(KEY_ENTER)){
        //on remet le compteur à 0
        compteur = 0;

        //on remet les coordonnées de la balle par défaut
        ball.x = 100;
        ball.y = 100;
        ball.speed_x = 5;
        ball.speed_y = 5;

        //on remet les coordonnées du paddle par défaut
        paddle.speed = 5;   
        paddle.x = GetScreenWidth()/2-60;
        paddle.y = GetScreenHeight()-25;
        brick.x = GetRandomFloat(50.0f, GetScreenWidth() - brick.width - 10.0f);
        brick.y = GetRandomFloat(50.0f, GetScreenHeight() / 3.0f - brick.height - 10.0f);
    }
}


int main () {

    //longueur de l'écran
    const int SCREEN_WIDTH = 800;

    //largeur de l'écran
    const int SCREEN_HEIGHT = 600;
    
    //valeurs qu'on associe à la balle
    ball.x = 100;
    ball.y = 100;
    ball.radius = 10;
    ball.speed_x = 5;
    ball.speed_y = 5;
    
    //valeurs qu'on associe au Paddle
    paddle.x = SCREEN_WIDTH/2-60;
    paddle.y = SCREEN_HEIGHT-25;
    paddle.width = 120;
    paddle.height = 25;
    paddle.speed = 5;

    //valeurs qu'on associe à la brique
    brick.width = 100;
    brick.height = 20;
    brick.x = GetRandomFloat(50.0f, GetScreenWidth() - brick.width - 10.0f);
    brick.y = GetRandomFloat(50.0f, GetScreenHeight() / 3.0f - brick.height - 10.0f);
    
    
    //vairable pour faire pause ou reprendre
    bool flag = true;

    //cout << "Hello World" << endl;

    //titre affiché en haut à gauche du programme
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game created by Nam Nguyen");
    SetTargetFPS(120);

    

    //tant que la fenêtre est ouverte
    while (WindowShouldClose() == false){
        
        //si la balle est tombée, on appele la fonction GameOver
        if(ball.y + ball.radius >= GetScreenHeight()){
            GameOver();
        }    
    
        //si l'utilisateur appuit sur espace, si le jeu est en cours, on met pause, 
        if(IsKeyPressed(KEY_SPACE)){
            if(flag == true){
                flag = false;
            }
            //si le jeu est en pause, on reprend le jeu,    
            else if(flag==false){
                flag = true;
            }
        }
        
        //message affiché lorsque le jeu est en pause
        if(flag==false) DrawText("Pause", SCREEN_WIDTH/2-90, SCREEN_HEIGHT/2-25, 50, BLACK);

        //couleur du fond d'écran, et ça nous permet de supprimer les traces qu'on laisse derrière, pour la balle 
        //et le paddle
        ClearBackground(BLUE);    
        
        
        //dessiner le canvas (toile), l'espace sur lequel se trouve la balle et les raquettes
        BeginDrawing();
                
        //dessiner la balle (aapel à la fonction Draw de la classe Ball pour l'instance ball)
        ball.Draw();

        //dessiner la balle (aapel à la fonction Draw de la classe Paddle pour l'instance paddle)
        paddle.Draw();
        
        //dessiner la brique (aapel à la fonction Draw de la classe Brick pour l'instance brick)
        brick.Draw();
        
        //si le jeu est en cours, on met à jour les déplacements du paddle et de la balle
        if(flag == true){
            //mettre à jour les informations
            ball.Update();
            paddle.Update();
        }        

        //collision entre le paddle et la balle
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height})){
            //possible de faire avec des formules mathématiques arccos, arcsin, mais c'est plus simple de cette manière
            ball.speed_y *= -1;
        }    

        
        //collision entre la brique et le paddle
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{brick.x, brick.y, brick.width, brick.height})){
            //possible de faire avec des formules mathématiques arccos, arcsin, mais c'est plus simple de cette manière
            ball.speed_y *= -1;
            //incrémentation du compteur de 1
            compteur += 1;
            //on utilise toujours la même brique mais on change son emplacement juste
            brick.x = GetRandomFloat(50.0f, GetScreenWidth() - brick.width - 10.0f);
            brick.y = GetRandomFloat(50.0f, GetScreenHeight() / 2.0f - brick.height - 10.0f);
        }   
        
        //affichage du score pour l'utilisateur
        DrawText(TextFormat("Score: %i", compteur), 10, 10, 30, BLACK);

        //DrawRectangle(SCREEN_WIDTH/2-60, SCREEN_HEIGHT-25, 120, 25, WHITE);
        //arreter le canvas (toile)
        EndDrawing();
    }
}            
