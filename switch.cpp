#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int OUT = 64;

// Color palette (keep 1..7 compatible with your Sonic array)
enum SpriteColor {
    EMPTY = 0,
    BLUE = 1,
    YELLOW = 2,
    RED = 3,
    GREEN = 4,
    WHITE = 5,
    BLACK = 6,
    PEACH = 7,
    LIGHT_BLUE = 8,
    DARK_BLUE = 9,
    ORANGE = 10,
    GOLD = 11,
    GRAY = 12,
    DARK_GREEN = 13,
    PINK = 14,
    BROWN = 15,
    DARK_RED = 16
};

void pixel(int c) {
    switch(c) {
        case BLUE:       cout << "\033[48;5;27m  \033[0m"; break;
        case LIGHT_BLUE: cout << "\033[48;5;81m  \033[0m"; break;
        case DARK_BLUE:  cout << "\033[48;5;19m  \033[0m"; break;
        case RED:        cout << "\033[48;5;196m  \033[0m"; break;
        case DARK_RED:   cout << "\033[48;5;88m  \033[0m"; break;
        case GREEN:      cout << "\033[48;5;46m  \033[0m"; break;
        case DARK_GREEN: cout << "\033[48;5;22m  \033[0m"; break;
        case YELLOW:     cout << "\033[48;5;226m  \033[0m"; break;
        case ORANGE:     cout << "\033[48;5;208m  \033[0m"; break;
        case GOLD:       cout << "\033[48;5;214m  \033[0m"; break;
        case WHITE:      cout << "\033[48;5;15m  \033[0m"; break;
        case GRAY:       cout << "\033[48;5;245m  \033[0m"; break;
        case BLACK:      cout << "\033[48;5;16m  \033[0m"; break;
        case PEACH:      cout << "\033[48;5;223m  \033[0m"; break;
        case PINK:       cout << "\033[48;5;213m  \033[0m"; break;
        case BROWN:      cout << "\033[48;5;94m  \033[0m"; break;
        default:         cout << "  "; break;
    }
}

void drawBuffer(const vector<vector<int>>& buf) {
    for(int i=0;i<OUT;i++){
        for(int j=0;j<OUT;j++) pixel(buf[i][j]);
        cout << "\n";
    }
    cout << "\n";
}

void setPix(vector<vector<int>>& buf, int y, int x, int c){
    if(y>=0 && y<OUT && x>=0 && x<OUT) buf[y][x]=c;
}

void fillCircle(vector<vector<int>>& buf, int cy, int cx, int r, int c){
    for(int y=cy-r; y<=cy+r; y++)
        for(int x=cx-r; x<=cx+r; x++){
            int dy=y-cy, dx=x-cx;
            if(dx*dx+dy*dy <= r*r) setPix(buf,y,x,c);
        }
}

void fillRect(vector<vector<int>>& buf, int y1,int x1,int y2,int x2,int c){
    for(int y=y1;y<=y2;y++)
        for(int x=x1;x<=x2;x++)
            setPix(buf,y,x,c);
}

bool pointInTri(float px,float py,float ax,float ay,float bx,float by,float cx,float cy){
    float v0x=cx-ax, v0y=cy-ay;
    float v1x=bx-ax, v1y=by-ay;
    float v2x=px-ax, v2y=py-ay;
    float dot00=v0x*v0x+v0y*v0y;
    float dot01=v0x*v1x+v0y*v1y;
    float dot02=v0x*v2x+v0y*v2y;
    float dot11=v1x*v1x+v1y*v1y;
    float dot12=v1x*v2x+v1y*v2y;
    float invDen=1.0f/((dot00*dot11)-(dot01*dot01));
    float u=(dot11*dot02-dot01*dot12)*invDen;
    float v=(dot00*dot12-dot01*dot02)*invDen;
    return (u>=0)&&(v>=0)&&(u+v<=1);
}

void fillTriangle(vector<vector<int>>& buf, int ay,int ax,int by,int bx,int cy,int cx,int c){
    int minx=min(ax,min(bx,cx));
    int maxx=max(ax,max(bx,cx));
    int miny=min(ay,min(by,cy));
    int maxy=max(ay,max(by,cy));
    for(int y=miny;y<=maxy;y++)
        for(int x=minx;x<=maxx;x++)
            if(pointInTri(x,y, ax,ay, bx,by, cx,cy)) setPix(buf,y,x,c);
}

// ---- SONIC (40x40) ----
const int R=40,C=40;
int sonic[R][C]={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,5,3,1,1,1,1,1,1,1,1,1,1,1,3,5,1,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,5,3,1,1,1,1,1,1,1,1,1,1,1,3,5,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,6,6,6,6,6,6,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,1,1,2,2,2,2,6,6,6,6,6,6,6,6,6,6,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,2,2,2,6,6,6,6,6,6,6,6,6,6,6,6,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,2,2,2,6,6,6,6,6,6,6,6,6,6,6,6,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1},
{0,1,1,1,1,1,1,1,1,1,2,2,2,2,6,6,6,6,6,6,6,6,6,6,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,6,6,6,6,6,6,6,6,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0},
{0,0,0,0,0,4,4,4,4,4,4,4,4,4,3,3,0,0,0,0,3,3,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0},
{0,0,0,0,4,4,4,4,4,4,4,4,4,4,3,3,0,0,0,0,3,3,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void drawScaledFromSonic(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    for(int y=0;y<OUT;y++){
        for(int x=0;x<OUT;x++){
            int sy = y * R / OUT;
            int sx = x * C / OUT;
            buf[y][x] = sonic[sy][sx];
        }
    }
    drawBuffer(buf);
}

// ---- Procedural 64x64 sprites ----
void drawMushroom(bool green=false){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    int capColor = green ? GREEN : RED;

    fillCircle(buf, 24, 32, 20, capColor);
    fillCircle(buf, 24, 32, 20, (green?DARK_GREEN:DARK_RED));
    fillCircle(buf, 18, 32, 16, capColor);

    fillCircle(buf, 18, 20, 5, WHITE);
    fillCircle(buf, 18, 44, 5, WHITE);
    fillCircle(buf, 8, 32, 4, WHITE);

    fillRect(buf, 34, 24, 54, 40, WHITE);
    fillRect(buf, 34, 36, 54, 40, GRAY);

    drawBuffer(buf);
}

void drawGhost(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    fillCircle(buf, 22, 32, 18, WHITE);
    fillRect(buf, 22, 14, 46, 50, WHITE);
    for(int i=0;i<5;i++) fillCircle(buf, 48, 18+i*8, 4, WHITE);
    fillCircle(buf, 26, 24, 5, BLACK);
    fillCircle(buf, 26, 40, 5, BLACK);
    fillCircle(buf, 26, 24, 2, BLUE);
    fillCircle(buf, 26, 40, 2, BLUE);
    drawBuffer(buf);
}

void drawHeart(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    for(int y=0;y<OUT;y++){
        for(int x=0;x<OUT;x++){
            float fx = (x-32)/18.0f;
            float fy = (32-y)/18.0f; // fixed upright heart
            float eq = pow(fx*fx+fy*fy-1,3) - fx*fx*fy*fy*fy;
            if(eq <= 0) buf[y][x]=RED;
        }
    }
    drawBuffer(buf);
}

void drawPokeball(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    fillCircle(buf, 32, 32, 22, WHITE);
    fillCircle(buf, 32, 32, 22, BLACK);
    fillCircle(buf, 32, 32, 21, WHITE);
    for(int y=0;y<OUT;y++)
        for(int x=0;x<OUT;x++){
            int dy=y-32, dx=x-32;
            if(dx*dx+dy*dy <= 21*21){
                if(y<32) buf[y][x]=RED;
            }
        }
    fillRect(buf, 30, 12, 34, 52, BLACK);
    fillCircle(buf, 32, 32, 6, WHITE);
    fillCircle(buf, 32, 32, 3, BLACK);
    drawBuffer(buf);
}

void drawKirby(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    fillCircle(buf, 32, 32, 22, PINK);
    fillCircle(buf, 26, 24, 5, BLACK); // eyes
    fillCircle(buf, 26, 40, 5, BLACK);
    fillCircle(buf, 26, 24, 2, WHITE); // eye shine
    fillCircle(buf, 26, 40, 2, WHITE);
    fillCircle(buf, 36, 22, 4, DARK_RED); // blush
    fillCircle(buf, 36, 42, 4, DARK_RED);
    fillCircle(buf, 50, 20, 8, RED); // feet
    fillCircle(buf, 50, 44, 8, RED);
    drawBuffer(buf);
}

void drawPacman(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    for(int y=0;y<OUT;y++)
        for(int x=0;x<OUT;x++){
            int dy=y-32, dx=x-32;
            if(dx*dx+dy*dy <= 22*22){
                if(!(x>32 && abs(y-32) < (x-32)/2)) buf[y][x]=YELLOW;
            }
        }
    setPix(buf, 24, 40, BLACK);
    setPix(buf, 24, 41, BLACK);
    drawBuffer(buf);
}

void drawTriforce(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    fillTriangle(buf, 8,32, 28,12, 28,52, GOLD);
    fillTriangle(buf, 32,16, 52,0, 52,32, GOLD);
    fillTriangle(buf, 32,48, 52,32, 52,64, GOLD);
    drawBuffer(buf);
}

void drawMegaManHelmet(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));
    fillCircle(buf, 30, 32, 22, BLUE);
    fillCircle(buf, 26, 32, 18, LIGHT_BLUE);
    fillRect(buf, 30, 10, 52, 54, BLUE);
    fillRect(buf, 40, 22, 52, 42, DARK_BLUE);
    fillRect(buf, 18, 18, 30, 46, LIGHT_BLUE);
    drawBuffer(buf);
}

void drawSpaceInvader(){
    vector<vector<int>> buf(OUT, vector<int>(OUT,0));

    // Classic 11x8 invader pattern (scaled up)
    int inv[8][11] = {
        {0,0,1,0,0,0,0,0,1,0,0},
        {0,0,0,1,0,0,0,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,0,0},
        {0,1,1,0,1,1,1,1,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,1,0,1},
        {0,0,0,1,1,0,1,1,0,0,0}
    };

    // Scale each pixel to 4x4 and center it
    int scale = 4;
    int startY = 12;
    int startX = 10;

    for(int y=0;y<8;y++){
        for(int x=0;x<11;x++){
            if(inv[y][x]){
                for(int dy=0;dy<scale;dy++)
                    for(int dx=0;dx<scale;dx++)
                        setPix(buf, startY + y*scale + dy, startX + x*scale + dx, GREEN);
            }
        }
    }

    drawBuffer(buf);
}

int main(){
    int ch=0;
    while(true){
        cout << "\033[96m====== PIXEL SPRITE MAKER (64x64) ======\033[0m\n";
        cout << "1. Sonic (scaled from 40x40)\n";
        cout << "2. Mushroom (Red)\n";
        cout << "3. Ghost (white)\n";
        cout << "4. Heart (upright)\n";
        cout << "5. Pokeball\n";
        cout << "6. Kirby (improved)\n";
        cout << "7. Pac-Man\n";
        cout << "8. Triforce\n";
        cout << "9. 1-Up Mushroom\n";
        cout << "10. Mega Man Helmet\n";
        cout << "11. Space Invader (improved)\n";
        cout << "12. Exit\n";
        cout << "\nEnter Choice: ";
        if(!(cin>>ch)) break;
        if(ch==12) break;

        switch(ch){
            case 1: drawScaledFromSonic(); break;
            case 2: drawMushroom(false); break;
            case 3: drawGhost(); break;
            case 4: drawHeart(); break;
            case 5: drawPokeball(); break;
            case 6: drawKirby(); break;
            case 7: drawPacman(); break;
            case 8: drawTriforce(); break;
            case 9: drawMushroom(true); break;
            case 10: drawMegaManHelmet(); break;
            case 11: drawSpaceInvader(); break;
            default: cout << "Invalid Choice\n"; break;
        }
    }
    return 0;
}