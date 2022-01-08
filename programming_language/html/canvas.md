# Learning about <canvas>

## Disabling interpolation when scaling canvas

### E.g:
`<canvas id='b' width='21' height='21'></canvas>` will create a canvas object with 21x21 resolution.

`canvas#b { width: 105px; height: 105px; } /* 5 * 21 = 105 */` will create a canvas object with size 105x105.

The drawings rendered by the canvas will be stretched 5x. For pixelated drawings, the lines will appear blurred.

https://stackoverflow.com/questions/7615009/disable-interpolation-when-scaling-a-canvas <- `image-rendering: pixelated` as a css attribute should solve it.


## Why you should draw on the 0.5!! WAH!
http://diveintohtml5.info/canvas.html#pixel-madness

