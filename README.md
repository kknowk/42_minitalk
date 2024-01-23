# プロジェクトタイトル

42_minitalk

## 概要

serverのPID（プロセスID）を取得し、clientとの通信をはかります。

## 動機

42Tokyoの課題であり、また、  
UNIX シグナルを使用して小さなデータ交換プログラムをコーディングし、  
サーバーとクライアントの相互通信、シグナルハンドラの処理の理解が得られるため作成しました。

## 使用方法

ここではserver側とclient側の二つのターミナルを使用します。

> - **server**
> ```bash php
> #!/bin/bash
> cd 42_minitalk
> make
> ./server &
> (任意のPIDが出力されます)
> ```

> - **client**
> ```bash php
> #!/bin/bash
> cd 42_minitalk
> ./client (先ほど出力されたserverのPID) （任意の文字列）
> ```

server側にclient側で入力した任意の文字列が出力されます。

## 技術スタック

C言語

