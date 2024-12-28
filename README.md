# STEMS MIDI: MIDI Controller for Traktor Stems (Dev board)

[日本語はこちら(Document in Japanese)](./README.ja.md)

<img src = "images/90fe9efa438a586b2a142ccadcf6a3365e1b73369b2c3a177be453c0a366e1b7.png" width="350">
<img src = "images/4d9c5061edd3527730e51c4f8d3e0bc7af639b3db9c1c84aa4b2f6da778b346d.png" width="500">

## ChangeLog

### Rev. 1.1

- [Hardware] Remove center-click feature for Vol and Effect knobs
- [Hardware] Add testing terminals on PCB
- [Software] Add Information shown when connectiong to PC

## Kit Contents

<img src = "images/1d4c8b63cd5421fc718316e5a197efda357b795f54dc7dd9b1c2264ad3c7edcb.png" width="500">

- Pre-assembled PCB
- MCU Module Seeeduino XIAO RP2040(with flashed "sample" program)
- Pin Socket 1x7 (2 pcs.)
- Pin Header 1x7 (2 pcs.)
- Knob Caps (24 pcs.)
- Tactile switch Caps (24 pcs.)
- M3 Nuts (6 pcs.)
- M3 10mm Hex Spacers (6 pcs.)
- M3 7mm Hex Spacers (6 pcs.)
- M3 Screws (6 pcs.)
- Rubber feet pads(4 pcs.)
- Bottom Acrylic Panel (1 pcs.)
- Top Acrylic Panel (1 pcs.)

## Requied Equipments

- Solder Iron, Solder
- No.2 + Driver
- Plier and/or Wrench (for tightening nuts)

<img src="images/863d9f87f1b46fc23daa73ad291905975562b02c1ceab6e0338760c18eadf529.png" width="500">

## How to assemble

### Assemble the MCU Module

Recommend following procedure to align pins.
tips: You can solder MCU Module directly on the PCBA board.

Solder Pin Sockets, Pin Headers, and MCU. 1st, combine Pin Sockets and Headers as show below:

<img src="images/c11683a3c35204939dd786d694523f4b525355ddd5a23119c3f7ddc67c30a39e.png" width="500">

Put above result into MCU's both side holes as shown below:

<img src="images/5beeb27816afa18ad8dd069d9c9414cf212e1c5a50bae3524996a1ad0b696709.png" width="500">

Put them on the holes of PCBA below:

<img src="images/9d322c537f8b335544344cd8a2cc5b920bac66dcbd63934a199c60fc65fa0f9f.png" width="500">

Solder the Pin Header's MCU side:

<img src="images/6038161b53da7dc3d0ec92a8c922fd926f25249a085f5d71c1c7bdeaea71678c.png" width="500">

Looks like below:

<img src="images/393fb5d819d65040379703d6e247d5ef396053703a45fa2a1eae8a15508ac9fc.png" width="500">

Put it again on the PCBA's holes:

<img src="images/9d322c537f8b335544344cd8a2cc5b920bac66dcbd63934a199c60fc65fa0f9f.png" width="500">

Flip the PCBA board while holding the MCU module, with placing knob cap between MCU and the desk so that it can be held in place by its own weight.

Looks like below:

<img src="images/fa603afa1ce076bc8d2b96c47375e37aeff4e16acc9f735b7ce772b9d4e3e5ce.png" width="500">

Solder all the Pin socket's pin:

<img src="images/ddc43490427534982101d633568f0e675b127e7f4fbcef37d54b1cc8c4417cea.png" width="500">

### Assembling case

Peel off the protective sheet from the bottom acrylic panel, and attach nuts, M3  7mm Hex spacers hex screws (the shorter ones) at six locations.
(There are no two sides to the acrylic.):

<img src="images/353b8dc77a7f0ab9deea103f4629dd094ac2d2ac35ea92f73048b18d0484d7bf.png" width="500">

<img src="images/3ac4cbdde98af74f0cce6957054cb3b777a7afb91ab713df4ffe9abc72dfb181.png" width="500">

Put PCBA bord on it, tighten with the M3 10mm hex screws (the longer ones).
Tighten each screw little by little at to align the overall position:

<img src="images/1e16f55000933cda29fe15d2064a4ddfe24624cdf75c29e829f8ace4760dae51.png" width="500">

<img src="images/5affcbb84872de8d4f42be53c0941bd00284e82b639e03cf016ad98db60cfb2e.png" width="500">

Peel of the protective sheet from top acrylic panel and put it on the PCBA.
Tighten them with M3 screws.
Again, tighten each screw little by little at to align the overall position:

<img src="images/54e61845fd3b3c567229af5796d615cdf5245531f6204980dba667f84aea9ad8.png" width="500">

Put rubber feets on the bottom:

<img src="images/250c74b7f399b8d5f54edf250d41a127c9ddc31698e49df8d03a7017829ed84c.png" width="500">

Place knob caps:

<img src="images/e4e5d0f3ab611a4637d379048362ccbdaae4dab5ac585c91589651640e6fc288.png" width="500">

Place tactile switch caps:

<img src="images/583bcc246504249e1f59c90b10270863853a2a8c90c9fe83e984703308507fdd.png" width="500">

## Usage

- Connect the product to PC/MAC.
- Import .tsi file below on Traktor.

<https://github.com/kinoshita-lab/StemsMIDI/tree/main/Traktor%20Setting>
