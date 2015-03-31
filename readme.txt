■mine sweeper ver 0.01
2000/6/8

【概要】
マインスイーパーです。
ベンチマーク付き。

【動作環境】
画面が800x600、16bit以上で、次のOSを使用しているコンピュータ。
	Linux
	Windows9x
	BeOS
	FreeBSD4.0
	Irix
SDL-1.1.3以降をインストールしている必要があります

【同梱ファイル】
readme.txt	このファイル
Makefile	メイクファイル
*.c/*.h		各種ソースファイル
Copying		Lesser GNU General Public License documentation
*.bmp		グラフィックファイル
graph.txt	グラフィック指定ファイル

【動作方法】
■コンパイル
makeと打つだけです

■プレイ方法

%./mineでプログラムが開始します。

爆弾をよけてすべてのパネルを開ければクリアです。
パネルを開けて幸運にも爆弾を引かなかった場合、周囲の８マスにある爆弾の数が表示されます。表示されない場合、爆弾はありません。

右下のRestartをクリックすると同じ条件でもう一度プレイできます。もちろん爆弾の位置は変わります。
Quit Gameをクリックするとゲームを終了します。

ゲーム中に右クリックを押すとゲーム条件を変えることが出来ます。もう一度右クリックすることでゲームに戻ります。
Bomb Ratio	爆弾の入る確率を変更します。
Game size	ステージのサイズを変えます。
条件の変更はゲーム中にRestartを押すことで有効になります。

F12を押すとゲームのスクリーンショットを取ります。

【更新履歴】

2000/6/8	ver0.01

【その他】
このプログラムはSimple DirectMedia Layer(SDL)を利用してプログラムされています。SDLの最新版は
http://www.devolution.com/~slouken/SDL/license.html
にあります。SDLはLGPLにしたがって配布されています。


【配布条件】
LGPLに従います。

Copyright 2000,adas
E-Mail	adas@geocities.co.jp
URL	http://www.geocities.co.jp/Berkeley/2093
