let font;
let input;

function preload() {
    font = loadFont("fonts/SourceCodePro-Medium.ttf");
    input = loadStrings("inputs/day01-input.txt");
}

function setup() {
    createCanvas(600, 400);
    textFont(font);
    frameRate(60);
}

let reverse = s => s.split("").reverse().join("");
function calibrationValue(line) {
    let keys = [
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    let pos = [];
    let reversePos = [];
    for (let k of keys) {
        pos.push(line.indexOf(k));
        let rp = reverse(line).indexOf(reverse(k));
        reversePos.push(rp < 0 ? -1 : line.length - (rp + k.length));
    }
    let i1 = Math.min(...(pos.filter(x=>x!=-1)));
    let i2 = Math.max(...(reversePos.filter(x=>x!=-1)));
    let key1 = pos.indexOf(i1);
    let key2 = reversePos.indexOf(i2);

    return {
        key1: [i1, i1 + keys[key1].length],
        val1: key1 < 9 ? key1 + 1 : key1 - 9,
        key2: [i2, i2 + keys[key2].length],
        val2: key2 < 9 ? key2 + 1 : key2 - 9
    }
}

let frame = 0;
let curLineI = 0;
let sidebarW = 50;
let values = [];
let total = 0;

let addedTotal = false;
function draw() {
    background(15, 15, 35);
    let inputLine = input[curLineI];
    let cal = calibrationValue(inputLine);
    let keys = inputLine.split("").fill(" ");
    keys.splice(cal.key1[0], cal.key1[1]-cal.key1[0], ...(inputLine.slice(cal.key1[0], cal.key1[1])));
    keys.splice(cal.key2[0], cal.key2[1]-cal.key2[0], ...(inputLine.slice(cal.key2[0], cal.key2[1])));
    keys = keys.join("");
    let value = cal.val1 + "" + cal.val2;

    noStroke();
    textAlign(CENTER, CENTER);
    textSize(Math.min(Math.floor((width-sidebarW)*0.97/(inputLine.length*0.6)), 60));
    fill(255);
    let lineBounds = font.textBounds(inputLine, (width-sidebarW)/2, height/2.1);

    // Text fade-in animation - Frame 10 - 30
    text(inputLine, (width-sidebarW)/2, height/2.1);
    if (frame > 10) {
        if (frame < 30) {
            fill(255, 255, 80, lerp(0, 255, (frame-10)/20));
        } else {
            fill(255, 255, 80);
        }
        text(keys, (width-sidebarW)/2, height/2.1);
    }

    // Value fade-in and center motion - Frame 30 - 80
    if (frame > 30 && frame <= 80) {
        let keyWidth1 = textWidth(inputLine.slice(0, cal.key1[0]));
        let keyWidth2 = textWidth(inputLine.slice(0, cal.key2[0]));

        textSize(textSize()/1.2);

        let startX1 = lineBounds.x + keyWidth1 + textWidth(inputLine.slice(cal.key1[0], cal.key1[1]))/2;
        let startX2 = lineBounds.x + keyWidth2 + textWidth(inputLine.slice(cal.key2[0], cal.key2[1]))/2;
        let endX1 = font.textBounds("XX", (width-sidebarW)/2, height/2.1 + textSize()*1.1).x + textWidth("X")/2.6;
        let endX2 = endX1 + textWidth("X");
        let easing = x => x < 0.5 ? 2 * x * x : 1 - Math.pow(-2 * x + 2, 2) / 2;

        if (frame < 50) {
            fill(255, lerp(0, 255, (frame-30)/20));
            text(cal.val1, startX1, height/2.1 + textSize()*1.1);
            text(cal.val2, startX2, height/2.1 + textSize()*1.1);
        } else {
            fill(255);
            text(cal.val1, lerp(startX1, endX1, easing((frame-50)/30)), height/2.1 + textSize()*1.1);
            text(cal.val2, lerp(startX2, endX2, easing((frame-50)/30)), height/2.1 + textSize()*1.1);
        }
    }

    if (frame > 80) {
        let easing1 = x => 2.70158 * x * x * x - 1.70158 * x * x;
        fill(255);

        if (frame < 125) {
            textSize(lerp(textSize()/1.2, 30, (frame-80)/45));
            text(
                value, 
                lerp((width-sidebarW)/2, 577, easing1((frame-80)/45)),
                lerp(height/2.1 + textSize()*1.1, 335, easing1((frame-80)/45))
            );
        } else {
            if (!addedTotal) {
                addedTotal = true;
                values.unshift(value);
                values = values.slice(0, 10);
                total += parseInt(value);
            }
        }
    }

    fill(255)
    textSize(30);
    let y = addedTotal ? 335 : 300;
    if (frame > 130) {
        y = lerp(y, y - 35, (frame-130)/20);
    }
    for (let val of values) {
        text(val, 577, y);
        y -= 35;
    }

    stroke(255);
    strokeWeight(2);
    line(505, 360, width, 360);

    fill(255);
    textSize(30);
    textAlign(TOP, LEFT);
    noStroke();
    text("Total: " + total.toString().padStart(5, "0"), 380, 390);
    
    frame += 67;
    if (frame > 150) {
        if (!addedTotal) {
            addedTotal = true;
            values.unshift(value);
            values = values.slice(0, 9);
            total += parseInt(value);
        }
        curLineI++;
        if (curLineI >= input.length) {
            frame = 150;
            curLineI = input.length-1;
        } else {
            addedTotal = false;
            frame = 0;
        }
    }
}

function forward() {
    frame = 0;
    curLineI++;
}