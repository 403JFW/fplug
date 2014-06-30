fplug
=====

F-PLUG を Linux から利用するためのユーティリティ群.

record_fplug.c
--------------
F-PLUG から情報を取得し, 日時と気温, 湿度, 照度, 消費電力を標準出力に出力するプログラム.

record_fplug.sh
---------------
record_fplug.c を用いて取得したデータを CSV ファイルに蓄積するスクリプト.
rsync を用いて他のサーバーへデータの転送を行うことも可能.

run_rfcomm.sh
-------------
rfcomm で F-PLUG に接続し, 接続が切断された場合は自動的に再接続を行うシェルスクリプト.

Special thanks
--------------
[fplug_for_linux](https://github.com/goto2048/fplug_for_linux)
