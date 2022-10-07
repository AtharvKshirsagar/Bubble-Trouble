#include <simplecpp>
#include "shooter.h"
#include "bubble.h"
#include <cmath>
#include <sstream>
#include <string>
#include <time.h>

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


bool shooter_dead = false;

//level of game. 3 levels.
int level = 3;

//lives of game. 3 lives.
int lives = 3;

//collision wont work again once if shooter lost a life and the object isnt away yet
bool in = false;

//score count
int score = 0;
bool update_score = false;

//track time
bool init_time = false;
time_t time_start;


//to check collision between bubbles and bullets
void check_collision_bullets_bubbles(vector<Bubble> &bubbles, vector<Bullet> &bullets, vector<int> &levels){


    vector<int> bubbles_remove;
    vector<int> bullets_remove;

    vector<int> add_pos_x;
    vector<int> add_pos_y;

    vector<int> track_levels;

    int prev_i = -1;

    // cout << "starat " << endl;

    for (int j=0; j < bubbles.size(); j++)
    {
        for(int i=0; i < bullets.size(); i++){

            // cout << "hh " << i << " " << j << endl;

            double left_down_corner_bullet_x = bullets[i].get_center_x() - bullets[i].get_width()/2;
            double right_down_corner_bullet_x = bullets[i].get_center_x() + bullets[i].get_width()/2;
            double left_up_corner_bullet_x = bullets[i].get_center_x() - bullets[i].get_width()/2;
            double right_up_corner_bullet_x = bullets[i].get_center_x() + bullets[i].get_width()/2;
            double left_center_bullet_x = bullets[i].get_center_x() - bullets[i].get_width()/2;
            double right_center_bullet_x = bullets[i].get_center_x() + bullets[i].get_width()/2;
            double top_center_bullet_x = bullets[i].get_center_x();
            double bottom_center_bullet_x = bullets[i].get_center_x();
            double left_down_corner_bullet_y = bullets[i].get_center_y() + bullets[i].get_height()/2;
            double right_down_corner_bullet_y = bullets[i].get_center_y() + bullets[i].get_height()/2;
            double left_up_corner_bullet_y = bullets[i].get_center_y() - bullets[i].get_height()/2;
            double right_up_corner_bullet_y = bullets[i].get_center_y() + bullets[i].get_height()/2;
            double left_center_bullet_y = bullets[i].get_center_y();
            double right_center_bullet_y = bullets[i].get_center_y();
            double top_center_bullet_y = bullets[i].get_center_y() - bullets[i].get_height()/2;
            double bottom_center_bullet_y = bullets[i].get_center_y() + bullets[i].get_height()/2;

            bool collided = false;

            if (sqrt(pow((left_down_corner_bullet_x - bubbles[j].get_center_x()), 2) + pow((left_down_corner_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((right_down_corner_bullet_x - bubbles[j].get_center_x()), 2) + pow((right_down_corner_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((left_up_corner_bullet_x - bubbles[j].get_center_x()), 2) + pow((left_up_corner_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((right_up_corner_bullet_x - bubbles[j].get_center_x()), 2) + pow((right_up_corner_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((left_center_bullet_x - bubbles[j].get_center_x()), 2) + pow((left_center_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((right_center_bullet_x - bubbles[j].get_center_x()), 2) + pow((right_center_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((top_center_bullet_x - bubbles[j].get_center_x()), 2) + pow((top_center_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            } else if (sqrt(pow((bottom_center_bullet_x - bubbles[j].get_center_x()), 2) + pow((bottom_center_bullet_y - bubbles[j].get_center_y()), 2)) <= bubbles[j].get_radius()){
                collided = true;
            }


            if (collided){

                // cout << bubbles[j].get_radius() << endl;

                // cout << "collided " << i << " " << j << endl;

                // cout << "hmm: " << &bullets[i] << endl;

                // bool no_dupl = false;

                // for(int h = 0; h < bullets.size(); h++){
                    // if (h != i){
                        // cout << &bullets[h] << " " << &bullets[i] << endl;
                        // if (bullets[h] == bullets[i]){
                            // no_dupl = true;
                        // }
                    // }
                // }

                // if(no_dupl){
                    // no_dupl = false;
                // }

                if (prev_i != i){

                    bullets_remove.push_back(i);
                    prev_i = i;

                }

                bubbles_remove.push_back(j);


                score += 1;
                update_score = true;

                // if (levels[j] == 3){


                    // levels[j] = 2;

                    // track_levels.push_back(3);

                    int bullet_x = bubbles[j].get_center_x();
                    int bullet_y = bubbles[j].get_center_y();

                    // cout << "3 " << bullet_x << " " << bullet_y << endl;
                    
                    add_pos_x.push_back(bullet_x);
                    add_pos_y.push_back(bullet_y);

                    // bubbles.push_back(Bubble(bullet_x - BUBBLE_DEFAULT_RADIUS, bullet_y, BUBBLE_DEFAULT_RADIUS*2, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
                    // bubbles.push_back(Bubble(bullet_x + BUBBLE_DEFAULT_RADIUS, bullet_y, BUBBLE_DEFAULT_RADIUS*2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));


                // } else if (levels[j] == 2){

                    // track_levels.push_back(2);

                    // int bullet_x = bubbles[j].get_center_x();
                    // int bullet_y = bubbles[j].get_center_y();

                    // cout << "2: " << bullet_x << " " << bullet_y << endl;

                    // add_pos_x.push_back(bullet_x);
                    // add_pos_y.push_back(bullet_y);

                    // bubbles.push_back(Bubble(bullet_x - BUBBLE_DEFAULT_RADIUS*2, bullet_y, BUBBLE_DEFAULT_RADIUS*2, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
                    // bubbles.push_back(Bubble(bullet_x + BUBBLE_DEFAULT_RADIUS*2, bullet_y, BUBBLE_DEFAULT_RADIUS*2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));

                // }

            }

        }
    }

    // cout << "endd " << endl;

    for (unsigned int k=0; k < bullets_remove.size(); k++)
    {

        // cout << "chbullet: " << k << endl;

        bullets.erase(bullets.begin()+bullets_remove[k]);
    }

    // for (int p = 0; p < levels.size(); p++){
    //     cout << levels[p] << " ";
    // }

    // cout << endl;

    // if (bubbles_remove.size() > 0){

    //     cout << "checkkkkkk " << endl;

    //     for (int p = 0; p < bubbles_remove.size(); p++){
    //         cout << bubbles_remove[p] << " ";
    //     }

    //     cout << endl;

    // }

    // if (bubbles_remove.size() > 0){

    //     cout << "checkkkkkk22222 " << endl;

    //     for (int p = 0; p < add_pos_x.size(); p++){
    //         cout << add_pos_x[p] << " ";
    //     }

    //     cout << endl;

    // }

    for (int k=bubbles_remove.size()-1; k >= 0; k--)
    {

        // cout << "chbubble: " << k << endl;


        // cout << "ji2" << endl;

        int bullet_x = bubbles[bubbles_remove[k]].get_center_x();
        int bullet_y = bubbles[bubbles_remove[k]].get_center_y();

        if (bubbles[bubbles_remove[k]].get_radius() == 40){

            // levels.push_back(3);
            // levels.push_back(3);

            // cout << "cjecl1 " << add_pos_x[k] << " " << add_pos_y[k] << endl;
            
            bubbles.push_back(Bubble(bullet_x - BUBBLE_DEFAULT_RADIUS, bullet_y, BUBBLE_DEFAULT_RADIUS*2, -BUBBLE_DEFAULT_VX, bubbles[bubbles_remove[k]].get_vy(), COLOR(255,105,180)));
            bubbles.push_back(Bubble(bullet_x + BUBBLE_DEFAULT_RADIUS, bullet_y, BUBBLE_DEFAULT_RADIUS*2, BUBBLE_DEFAULT_VX, bubbles[bubbles_remove[k]].get_vy(), COLOR(255,105,180)));

        } else if (bubbles[bubbles_remove[k]].get_radius() == 20){

            // levels.push_back(2);
            // levels.push_back(2);

            // cout << "cjecl2 " << add_pos_x[k] << " " << add_pos_y[k] << endl;

            bubbles.push_back(Bubble(bullet_x - BUBBLE_DEFAULT_RADIUS*2, bullet_y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, bubbles[bubbles_remove[k]].get_vy(), COLOR(255,105,180)));
            bubbles.push_back(Bubble(bullet_x + BUBBLE_DEFAULT_RADIUS*2, bullet_y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, bubbles[bubbles_remove[k]].get_vy(), COLOR(255,105,180)));

        }

        bubbles.erase(bubbles.begin()+bubbles_remove[k]);


        // levels.erase(levels.begin()+bubbles_remove[k]);

    }

    // cout << "ji" << endl;

    // bubbles_remove = {};
    // bullets_remove = {};

    // // cout << "g: " << add_pos_x.size() << endl;

    // for (int p = 0; p < track_levels.size(); p++){
       
    //     cout << "jj" << track_levels[p] << " ";
    // }

    // cout << endl;

    // for (int u = 0; u < add_pos_x.size(); u++){

    //     if (bubbles[u].get_radius() == 40){

    //         // levels.push_back(3);
    //         // levels.push_back(3);

    //         cout << "cjecl " << add_pos_x[u] << " " << add_pos_y[u] << endl;
            
    //         bubbles.push_back(Bubble(add_pos_x[u] - BUBBLE_DEFAULT_RADIUS, add_pos_y[u], BUBBLE_DEFAULT_RADIUS*2, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    //         bubbles.push_back(Bubble(add_pos_x[u] + BUBBLE_DEFAULT_RADIUS, add_pos_y[u], BUBBLE_DEFAULT_RADIUS*2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));

    //     } else if (track_levels[u] == 2){

    //         // levels.push_back(2);
    //         // levels.push_back(2);

    //         cout << "cjecl2 " << add_pos_x[u] << " " << add_pos_y[u] << endl;

    //         bubbles.push_back(Bubble(add_pos_x[u] - BUBBLE_DEFAULT_RADIUS*2, add_pos_y[u], BUBBLE_DEFAULT_RADIUS*2, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    //         bubbles.push_back(Bubble(add_pos_x[u] + BUBBLE_DEFAULT_RADIUS*2, add_pos_y[u], BUBBLE_DEFAULT_RADIUS*2, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));

    //     }

    // }

}


void check_collision_shooter_bubbles(vector<Bubble> &bubbles, Shooter &shooter, bool &shooter_dead){

    if (shooter_dead){
        shooter_dead = false;
    }

    for (unsigned int i=0; i < bubbles.size(); i++)
    {

        double left_down_corner_shooter_x = shooter.get_body_center_x() - shooter.get_body_width()/2;
        double right_down_corner_shooter_x = shooter.get_body_center_x() + shooter.get_body_width()/2;
        double left_up_corner_shooter_x = shooter.get_body_center_x() - shooter.get_body_width()/2;
        double right_up_corner_shooter_x = shooter.get_body_center_x() + shooter.get_body_width()/2;
        double left_center_shooter_x = shooter.get_body_center_x() - shooter.get_body_width()/2;
        double right_center_shooter_x = shooter.get_body_center_x() + shooter.get_body_width()/2;
        double top_center_shooter_x = shooter.get_body_center_x();
        double bottom_center_shooter_x = shooter.get_body_center_x();
        double left_down_corner_shooter_y = shooter.get_body_center_y() + shooter.get_body_height()/2;
        double right_down_corner_shooter_y = shooter.get_body_center_y() + shooter.get_body_height()/2;
        double left_up_corner_shooter_y = shooter.get_body_center_y() - shooter.get_body_height()/2;
        double right_up_corner_shooter_y = shooter.get_body_center_y() + shooter.get_body_height()/2;
        double left_center_shooter_y = shooter.get_body_center_y();
        double right_center_shooter_y = shooter.get_body_center_y();
        double top_center_shooter_y = shooter.get_body_center_y() - shooter.get_body_height()/2;
        double bottom_center_shooter_y = shooter.get_body_center_y() + shooter.get_body_height()/2;

        if (sqrt(pow((shooter.get_head_center_x() - bubbles[i].get_center_x()), 2) + pow((shooter.get_head_center_y() - bubbles[i].get_center_y()), 2)) <= (bubbles[i].get_radius() + shooter.get_head_radius())){
            shooter_dead = true;
        } else if (sqrt(pow((left_down_corner_shooter_x - bubbles[i].get_center_x()), 2) + pow((left_down_corner_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((right_down_corner_shooter_x - bubbles[i].get_center_x()), 2) + pow((right_down_corner_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((left_up_corner_shooter_x - bubbles[i].get_center_x()), 2) + pow((left_up_corner_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((right_up_corner_shooter_x - bubbles[i].get_center_x()), 2) + pow((right_up_corner_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((left_center_shooter_x - bubbles[i].get_center_x()), 2) + pow((left_center_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((right_center_shooter_x - bubbles[i].get_center_x()), 2) + pow((right_center_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((top_center_shooter_x - bubbles[i].get_center_x()), 2) + pow((top_center_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        } else if (sqrt(pow((bottom_center_shooter_x - bubbles[i].get_center_x()), 2) + pow((bottom_center_shooter_y - bubbles[i].get_center_y()), 2)) <= bubbles[i].get_radius()){
            shooter_dead = true;
        }
    }

}



void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}


string int_to_str(int num) {
    ostringstream text;
    text << num;
    return text.str();
}



vector<Bubble> create_bubbles(int level)
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    if (level == 1){
        bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    } else {
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS * pow(2, level-1), -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
        bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS * pow(2, level-1), BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
        bubbles.push_back(Bubble(WINDOW_X*3/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS * pow(2, level-1), BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    }

    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));
    
    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    string time_cmd("Time: 0/50");
    Text Time(LEFT_MARGIN, 5, time_cmd);

    string health_cmd("Health: 3/3");
    Text Health(WINDOW_X - 70, 5, health_cmd);

    string level_cmd("Level: 1/3");
    Text Level(WINDOW_X/2.0, BOTTOM_MARGIN, level_cmd);

    string score_cmd("Score: 0");
    Text Score(WINDOW_X - 70, BOTTOM_MARGIN, score_cmd);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles(level);

    vector<int> levels;

    for (int y = 0; y < bubbles.size(); y++){
        levels.push_back(3);
    }

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;


    // Main game loop
    while (true)
    {

        if (!init_time){
            // time_start = clock();
            init_time = true;
            time_start = time(0);

        } else {

            double tracked_time = difftime( time(0), time_start);

            // cout << tracked_time << endl;
            // cout << int_to_str(tracked_time) << endl;


            time_cmd = "Time: " + int_to_str(tracked_time) + "/50";
            Time.setMessage(time_cmd);

            if (tracked_time > 49){
                shooter_dead = true;
                break;
            }

        }

        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {   
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);
            
            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }
        
        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        // check if bullets and bubbles are colliding
        check_collision_bullets_bubbles(bubbles, bullets, levels);

        if (update_score){

            score_cmd =  "Score: " + int_to_str(score);
            Score.setMessage(score_cmd);
            
            update_score = false;

        }

        //check_empty_bubbles(bubbles);
        if (bubbles.size() == 0){

            bullets.clear();

            //Text congo(250, 250, "congratulations");
            break;
        }

        check_collision_shooter_bubbles(bubbles, shooter, shooter_dead);

        if (!in){
            if (shooter_dead){
                // cout << "pieces lives:" << lives << endl;

                shooter.setcolor(COLOR(0, 0, 0));

                lives -= 1;

                health_cmd[health_cmd.length() - 3] = '0' + lives;
                Health.setMessage(health_cmd);
            
                
                // bullets.clear();
                if (lives == 0){
                    break;
                }

                in = true;

                // cout << "pieces lives:" << lives << endl;
                
            }
        } else {
            if (!shooter_dead){
                // cout << '.' << endl;
                in = false;
                shooter.setcolor(COLOR(0, 255, 0));
            }
        }

        // cout << shooter_dead << endl;

        wait(STEP_TIME);
    }

    if (shooter_dead){
        Text congo(250, 250, "Game Over");
        congo.setColor(COLOR("red"));
        congo.imprint();
    } else {
        Text congo(250, 250, "congratulations");
        congo.setColor(COLOR("yellow"));
        congo.imprint();
    }
    

    wait(3);
}
