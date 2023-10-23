var cmyk_slider = document.getElementsByClassName("cmyk-slider");
var cmyk_in = document.getElementsByClassName("cmyk-in");
var rgb_slider = document.getElementsByClassName("rgb-slider");
var rgb_in = document.getElementsByClassName("rgb-in");
var hsv_slider = document.getElementsByClassName("hsv-slider");
var hsv_in = document.getElementsByClassName("hsv-in");
var chooser = document.getElementById("chooser");


update(0,0,0);
function update(r,g,b){
    document.body.style.backgroundColor = 'rgb(' + r + ', ' + g + ', ' + b + ')';  
    var text = document.getElementById("text"); 
    text.style.color = 'rgb(' + (255-r) + ', ' + (255-g) + ', ' + (255-b) + ')'; 
}


const hexToRgb = (hex) => {
    const r = parseInt(hex.slice(1, 3), 16);
    const g = parseInt(hex.slice(3, 5), 16);
    const b = parseInt(hex.slice(5, 7), 16);
    return [r,g,b];
}

function chooseColor() {
    setRgb.apply(this, hexToRgb(chooser.value));
    rgbSlider();
}




function changeFromRgb(r,g,b){
    setRgb(r,g,b);
    setCmyk.apply(this, rgbToCmyk(r,g,b));
    setHsv.apply(this, rgbToHsv(r,g,b));
}

function changeFromHsv(h,s,v){
    setHsv(h,s,v);
    setCmyk.apply(this, hsvToCmyk(h,s,v));
    setRgb.apply(this, hsvToRgb(h,s,v));
}

function changeFromCmyk(){
    setCmyk.apply(this, getCMYK());
    setRgb.apply(this, cmykToRgb());
    setHsv.apply(this, cmykToHsv());
}

function cmykToRgb(){
    var cmyk = getCMYK();
    var r = 255 * (1 - cmyk[0]) * (1 - cmyk[3]);
    var g = 255 * (1 - cmyk[1]) * (1 - cmyk[3]);
    var b = 255 * (1 - cmyk[2]) * (1 - cmyk[3]);
    return [Math.round(r),Math.round(g),Math.round(b)];
}

function rgbToHsv(r, g, b) {
    r /= 255;
  g /= 255;
  b /= 255;

  let cmax = Math.max(r, g, b);
  let cmin = Math.min(r, g, b);
  let delta = cmax - cmin;
  let h = 0;
  let s = 0;
  let l = 0;

  if (delta === 0) {
    h = 0;
  } else if (cmax === r) {
    h = ((g - b) / delta) % 6;
  } else if (cmax === g) {
    h = (b - r) / delta + 2;
  } else {
    h = (r - g) / delta + 4;
  }

  h = Math.round(h * 60);

  if (h < 0) {
    h += 360;
  }

  l = (cmax + cmin) / 2;

  if (delta === 0) {
    s = 0;
  } else {
    s = delta / (1 - Math.abs(2 * l - 1));
  }

  s = +(s * 100).toFixed(1);
  l = +(l * 100).toFixed(1);

  const round = (num) => Math.round(num);

  return [h, round(s),round(l)]
  }
  
  function hsvToRgb(h, s, l) {
h /= 360;
  s /= 100;
  l /= 100;

  let r, g, b;

  if (s === 0) {
    r = g = b = l;
  } else {
    const hue2rgb = (p, q, t) => {
      if (t < 0) t += 1;
      if (t > 1) t -= 1;
      if (t < 1 / 6) return p + (q - p) * 6 * t;
      if (t < 1 / 2) return q;
      if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
      return p;
    };

    const q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    const p = 2 * l - q;

    r = hue2rgb(p, q, h + 1 / 3);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 1 / 3);
  }

  const round = (num) => Math.round(num * 255);

  return [round(r),round(g), round(b)];
}
function cmykToHsv(){
    var rgb = cmykToRgb();
    var hsv = rgbToHsv(rgb[0], rgb[1], rgb[2]);
    return hsv;
}

function hsvToCmyk(h,s,v){
    var rgb = hsvToRgb(h,s,v);
    var cmyk = rgbToCmyk(rgb[0], rgb[1], rgb[2]);
    return cmyk;
}

function rgbToCmyk(r,g,b){
    var k = Math.min(1 - r/255, 1 - g/255, 1 - b/255);
    var c = (1 - r/255 - k)/(1 - k);
    var m = (1 - g/255 - k)/(1 - k);
    var y = (1 - b/255 - k)/(1 - k);
    return [c.toFixed(2),m.toFixed(2),y.toFixed(2),k.toFixed(2)];
}


function setCmyk(c,m,y,k){
    cmyk_slider[0].value = c;
    cmyk_slider[1].value = m;
    cmyk_slider[2].value = y;
    cmyk_slider[3].value = k;
    cmyk_in[0].value = c;
    cmyk_in[1].value = m;
    cmyk_in[2].value = y;
    cmyk_in[3].value = k;
}

function setRgb(r,g,b){
    rgb_slider[0].value = r;
    rgb_slider[1].value = g;
    rgb_slider[2].value = b;
    rgb_in[0].value = r;
    rgb_in[1].value = g;
    rgb_in[2].value = b;
}

function setHsv(h,s,v){
    hsv_slider[0].value = h;
    hsv_slider[1].value = s;
    hsv_slider[2].value = v;
    hsv_in[0].value = h;
    hsv_in[1].value = s;
    hsv_in[2].value = v;   
}

function getCMYK(){
    var c = cmyk_slider[0].value;
    var m = cmyk_slider[1].value;
    var y = cmyk_slider[2].value;
    var k = cmyk_slider[3].value;
    return [c,m,y,k];
}

function getCMYKin(){
    var c = cmyk_in[0].value;
    var m = cmyk_in[1].value;
    var y = cmyk_in[2].value;
    var k = cmyk_in[3].value;
    return [c,m,y,k];
}

function getRGB(){
    var r = rgb_slider[0].value;
    var g = rgb_slider[1].value;
    var b = rgb_slider[2].value;
    return [r,g,b];
}

function getRGBin(){
    var r = rgb_in[0].value;
    var g = rgb_in[1].value;
    var b = rgb_in[2].value;
    return [r,g,b];
}

function getHSV(){
    var h = hsv_slider[0].value;
    var s = hsv_slider[1].value;
    var v = hsv_slider[2].value;
    return [h,s,v];
}

function getHSVin(){
    var h = hsv_in[0].value;
    var s = hsv_in[1].value;
    var v = hsv_in[2].value;
    return [h,s,v];
}

function cmykSlider(){
    changeFromCmyk.apply(this, getCMYK());
    update(rgb_slider[0].value, rgb_slider[1].value, rgb_slider[2].value);
}

function cmykIn(){
    setCmyk.apply(this,getCMYKin());
    changeFromCmyk.apply(this,getCMYKin());
    update(rgb_in[0].value, rgb_in[1].value, rgb_in[2].value);
}

function rgbSlider(){
    changeFromRgb.apply(this, getRGB());
    update(rgb_slider[0].value, rgb_slider[1].value, rgb_slider[2].value);
}

function rgbIn(){
    setRgb.apply(this,getRGBin());
    changeFromRgb.apply(this,getRGBin());
    update(rgb_in[0].value, rgb_in[1].value, rgb_in[2].value);
}

function hsvIn(){
    setHsv.apply(this,getHSVin());
    changeFromHsv.apply(this,getHSVin());
    update(rgb_in[0].value, rgb_in[1].value, rgb_in[2].value);
}
function hsvSlider(){
    changeFromHsv.apply(this, getHSV());
    update(rgb_slider[0].value, rgb_slider[1].value, rgb_slider[2].value);
}
