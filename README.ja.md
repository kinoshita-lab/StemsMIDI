# STEMS MIDI Traktor Stems用MIDIコントローラ (開発キット)

<img src = "images/90fe9efa438a586b2a142ccadcf6a3365e1b73369b2c3a177be453c0a366e1b7.png" width="350">
<img src = "images/4d9c5061edd3527730e51c4f8d3e0bc7af639b3db9c1c84aa4b2f6da778b346d.png" width="500">

## ChangeLog

### ソフトウェア
releases(https://github.com/kinoshita-lab/StemsMIDI/releases)

### ハードウェア Rev. 1.1
- Filter 意外はセンタークリックではなくなりました
- 基板に検査用端子が追加されました

## キットに含まれるもの

<img src = "images/1d4c8b63cd5421fc718316e5a197efda357b795f54dc7dd9b1c2264ad3c7edcb.png" width="500">

- 部品実装済み基板
- マイコン Seeeduino XIAO RP2040(サンプル書き込み済み)
- ピンソケット 1x7 2個
- ピンヘッダ 1x7 2個
- ノブ 24個
- タクトスイッチキャップ(半透明) 24個
- ナット 6個
- 六角オネジ・メネジM3 10mm(長い方) 6個
- 六角オネジ・メネジM3 7mm(短かい方)  6個
- なべ小ねじ M3 6個
- ゴム足 4個
- 底用アクリル板
- 上用アクリル板

## 必要な工具

- はんだごて、はんだ
- +ドライバー(No.2)
- ラジオペンチ、もしくはM3のナットが締められるレンチなど

<img src="images/863d9f87f1b46fc23daa73ad291905975562b02c1ceab6e0338760c18eadf529.png" width="500">

## 組み立て方

### マイコンの組みたて

ピンなどがズレないように、下記の方法でのはんだづけを推奨します。
tips: ピンソケットを使わず、マイコンとピンヘッダを直接基板にはんだづけすることも可能です。用途に応じて、最初の手順を省いてください。

ピンソケット、ピンヘッダ、マイコンをはんだづけします。 まず、ピンソケットとピンヘッダを、下図のように組み合わせます。

<img src="images/c11683a3c35204939dd786d694523f4b525355ddd5a23119c3f7ddc67c30a39e.png" width="500">

組み合わせたものをマイコン左右の穴に挿入し、下図のように取りつけます。

<img src="images/5beeb27816afa18ad8dd069d9c9414cf212e1c5a50bae3524996a1ad0b696709.png" width="500">

基板の図の位置の穴に挿入します。

<img src="images/9d322c537f8b335544344cd8a2cc5b920bac66dcbd63934a199c60fc65fa0f9f.png" width="500">

この状態で、マイコンのピンをはんだづけします。

<img src="images/6038161b53da7dc3d0ec92a8c922fd926f25249a085f5d71c1c7bdeaea71678c.png" width="500">

このような状態になります。

<img src="images/393fb5d819d65040379703d6e247d5ef396053703a45fa2a1eae8a15508ac9fc.png" width="500">

再度、基板の図の位置の穴に挿入します。

<img src="images/9d322c537f8b335544344cd8a2cc5b920bac66dcbd63934a199c60fc65fa0f9f.png" width="500">

マイコンを押さえながら裏返しにし、机との間にノブを挟むなどして、自重で固定できるようにしながら裏返します。下図のようになります。

<img src="images/fa603afa1ce076bc8d2b96c47375e37aeff4e16acc9f735b7ce772b9d4e3e5ce.png" width="500">

ピンソケット(またはピンヘッダ)の足を全てはんだづけします。

<img src="images/ddc43490427534982101d633568f0e675b127e7f4fbcef37d54b1cc8c4417cea.png" width="500">

### ケースの組みたて

底用アクリル板の保護シートをはがし、6カ所に、ナット、六角オネジ・メネジM3 7mm(短い方)をとりつけます。アクリルに裏表はありません。

<img src="images/353b8dc77a7f0ab9deea103f4629dd094ac2d2ac35ea92f73048b18d0484d7bf.png" width="500">

<img src="images/3ac4cbdde98af74f0cce6957054cb3b777a7afb91ab713df4ffe9abc72dfb181.png" width="500">

基板を上に載せ、六角オネジ・メネジM3 10mm(長い方)を取りつけます。全体の位置を合わせながら、各ネジを少しずつ締めていきます。

<img src="images/1e16f55000933cda29fe15d2064a4ddfe24624cdf75c29e829f8ace4760dae51.png" width="500">

<img src="images/5affcbb84872de8d4f42be53c0941bd00284e82b639e03cf016ad98db60cfb2e.png" width="500">

上用アクリル板を載せ、なべ小ねじで締めます。全体の位置を合わせながら、各ネジを少しずつ締めていきます。

<img src="images/54e61845fd3b3c567229af5796d615cdf5245531f6204980dba667f84aea9ad8.png" width="500">

底面にゴム足を貼りつけます。

<img src="images/250c74b7f399b8d5f54edf250d41a127c9ddc31698e49df8d03a7017829ed84c.png" width="500">

ノブを取りつけます。

<img src="images/e4e5d0f3ab611a4637d379048362ccbdaae4dab5ac585c91589651640e6fc288.png" width="500">

タクトスイッチキャップを取りつけます。

<img src="images/583bcc246504249e1f59c90b10270863853a2a8c90c9fe83e984703308507fdd.png" width="500">

## 使い方

組みたてたものをPCに接続します。

<https://github.com/kinoshita-lab/StemsMIDI/tree/main/Traktor%20Setting> にある.tsiファイルをTraktorにインポートしてご利用ください。

## ソフトウェアのアップデート方法

必要なもの:

- <https://github.com/kinoshita-lab/StemsMIDI/releases> からダウンロードした、最新の firmware.uf2 ファイル
- PC または mac

マイコンの右下にある、 **B** ボタンを押しながらUSBケーブルを接続してください。
<img src="images/e19027d6f086a4644d27f2b9769c1e3397cf6c2087aafc610723d300e9c7c1cd.png" width="500">  

ボタンを離すと、ディスクドライブがPCかmac上に表示されます。ドライブ名は `RP-RP2` です。

<img src="images/bf1520c566c5de22c337de67e731d20b3598cbcd04bb74f23b3b1ca731d23071.png" width="800">

firmware.uf2をディスクドライブにコピーします。
<img src="images/74f0b672524e00f077c3da002e40ae39b642285c653c3a923f2d02379d6dfd68.png" width="800">

アップデートは以上で完了です。ドライブの表示は自動的に閉じます。
