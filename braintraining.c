/*****
      braintraining.c
      Kazuhito Tokita
      853554
      start: 2018.7.10

      中心にあるブラックボックスに向かって色付きの球が右から流れて来ます。
      ブラックボックスから球が出たり入ったりするので最終的にブラックボックスに
      残った球の数を色別で数えるゲームです。
*****/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<handy.h>

#define WINDOWSIZE 600 //画面の大きさ
#define RADIUS 30      //動く球の半径

int main() {

    doubleLayer layers; //ダブルバッファリングの変数を宣言する
    int size; //文字列の文字の大きさ
    int v=15; //球の動く速さ
    int x=630; //球の中心x座標
    int random; //乱数
    int RANDUM; //0~2の乱数
    int RANDUMarray; //ランダムな0~10の要素数
    int array[11]={5,6,7,8,9,10,11,12,13,14,15}; //最終的な球の合計値5~15の配列
    int count1=0; //ブラックボックスに残った赤玉の個数
    int count2=0; //ブラックボックスに残った青玉の個数
    int count3=0; //ブラックボックスに残った緑玉の個数
    int count; //ブラックボックスに残った球の合計
    int num1; //赤玉の答え入力
    int num2; //青玉の答え入力
    int num3; //緑玉の答え入力

    
    HgOpen(WINDOWSIZE,WINDOWSIZE*2/3);
    
    size=40;
    HgSetFillColor(HG_BLACK); //文字の色を黒色にする
    HgSetFont(HG_GB,size); //文字のフォントと大きさ
    HgText(80,200, "黒い箱に残った球の数を\n色ごとに数えてください",size);
    HgText(80,80,"START");
    HgSetFont(HG_GB,size/2); //文字のフォントと大きさ
    HgText(150,50,"(キーを押してください)");

    hgevent *event;              //
    HgSetEventMask(HG_KEY_DOWN); //キーを押したら
    HgGetEventMask();            //次のプログラムへと実行される
    event=HgEvent();             //


    srand(time(NULL)); //乱数を現在時刻で初期化する
    
    layers=HgWAddDoubleLayer(0); //ダブルレイヤを作成する

    random=rand();        //乱数を得る
    RANDUMarray=random%11;//RANDUMarrayを0~10のどれかとする
    
    for(;;){
        
        HgLClear(0);
        random=rand(); //乱数を得る
        RANDUM=random%3;    //RANDUMを0or1or2とする

        if(RANDUM==0 && x==630){//i=0の時スタート地点に戻ると
            HgWSetFillColor(0,HG_RED);//赤の
            count1++;                 //カウント1増える
        }
        else if(RANDUM==1 && x==630){//i=1の時スタート地点に戻ると
            HgWSetFillColor(0,HG_BLUE);//青の
            count2++;                  //カウント1増える
        }
        else if(RANDUM==2 && x==630){//i=2の時スタート地点に戻ると
            HgWSetFillColor(0,HG_GREEN);//緑の
            count3++;                   //カウント1増える
        }
        
        x-=v; //球のx座標が15ずつ減っていく
        
        if(count1>0){             //赤玉が一つでもブラックボックスに入っている時
            if(x==300){           //球がブラックボックス中心に来た時
                if(rand()%2){     //randが偶数の時
                    x=630;        //スタートに戻る
                }
                else{             //randが奇数の時          
                    HgWSetFillColor(0,HG_RED);//赤色に変わってそのまま進む
                    count1--;        //赤のカウント1減る
                }
            }
        }
        
        else if(count2>0){        //青玉が一つでもブラックボックスに入っている時
            if(x==300){           //球がブラックボックス中心に来た時
                if(rand()%2){     //randが偶数の時
                    x=630;        //スタートに戻る
                }
                else{             //randが奇数の時
                    HgWSetFillColor(0,HG_BLUE);//青色に変わってそのまま進む
                    count2--;        //青のカウント1減る
                }
            }
        }
        
        else if(count3>0){        //緑玉が一つでもブラックボックスに入っている時
            if(x==300){           //球がブラックボックス中心に来た時
                if(rand()%2){     //randが偶数の時
                    x=630;        //スタートに戻る
                }
                else{             //randが奇数の時
                    HgWSetFillColor(0,HG_GREEN);//緑色に変わってそのまま進む
                    count3--;       //緑のカウント1減る
                }
            }
        }
        
        if(x<-30){             //球が画面上から消えたら
            x=630;             //スタートに戻る
        }

            
        HgWCircleFill(0,x,RADIUS,RADIUS,1);//動く球
        
        HgSleep(0.05);       //0.05秒静止

        int lid = HgLSwitch(&layers);     //黒色のボックス
        HgWSetFillColor(lid,HG_BLACK);    //
        HgWBoxFill(lid,200,0,200,200,1);  //

        count=count1+count2+count3-1;//最終的に黒色のボックスに残った球の合計
        
        
        if(count==array[RANDUMarray]) //球の合計値がランダムで5~15の中から
            break;                    //選ばれた値になればfor文から抜け出す
        
    }
    //ここでゲーム終了！
    


    /*
      ここから下は答え入力から答え合わせのプログラム
    */
    

    if(RANDUM==0){        //最後はx座標630でもカウントしてしまうから一つ減らす
        count1=count1-1;  //
    }                     //
    else if(RANDUM==1){   //
        count2=count2-1;  //
    }                     //
    else{                 //
        count3=count3-1;  //                          
    }                     //

    HgText(80,200,"赤玉は？個\n青玉は？個\n緑玉は？個");

    printf("赤玉:");   //赤玉の答え入力
    scanf("%d",&num1); //

    printf("青玉:");   //青玉の答え入力
    scanf("%d",&num2); //

    printf("緑玉:");   //緑玉の答え入力
    scanf("%d",&num3); //

    HgClear();

    size=40;
    HgSetFont(HG_GB,size); //文字のフォントと大きさ
     

    if(num1==count1 && num2==count2 && num3==count3){  //正解の表示
        HgText(200,150,"お見事！\n\n正解です！");      //
        printf("お見事！正解です！\n");                //
    }
    else{                                              //不正解の表示
        HgText(200,260,"残念！  正解は");              //
        HgText(200,80,"赤玉%d個\n青玉%d個\n緑玉%d個",count1,count2,count3);//
        printf("残念！\n正解は\n");                    //
        printf("赤玉:%d個\n青玉:%d個\n緑玉:%d個\n",count1,count2,count3);//
    }                                                  
    
    
    HgSetEventMask(HG_KEY_DOWN); //キーを押したら
    HgGetEventMask();            //プログラム終了
    event=HgEvent();             //
 
     
    HgGetChar();
    HgClose();

    return 0;
}
 
    
