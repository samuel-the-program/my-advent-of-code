// https://easings.net/
const easings = {
    easeInSine: x => 1 - Math.cos((x * Math.PI) / 2),
    easeOutSine: x => Math.sin((x * Math.PI) / 2),
    easeInOutSine: x => -(Math.cos(Math.PI * x) - 1) / 2,
    easeInQuad: x => x * x,
    easeOutQuad: x => 1 - (1 - x) * (1 - x),
    easeInOutQuad: x => x < 0.5 ? 2 * x * x : 1 - Math.pow(-2 * x + 2, 2) / 2,
    easeInCubic: x => x * x * x,
    easeOutCubic: x => 1 - Math.pow(1 - x, 3),
    easeInOutCubic: x => x < 0.5 ? 4 * x * x * x : 1 - Math.pow(-2 * x + 2, 3) / 2,
    easeInQuart: x => x * x * x * x,
    easeOutQuart: x => 1 - Math.pow(1 - x, 4),
    easeInOutQuart: x => x < 0.5 ? 8 * x * x * x * x : 1 - Math.pow(-2 * x + 2, 4) / 2,
    easeInQuint: x => x * x * x * x * x,
    easeOutQuint: x => 1 - Math.pow(1 - x, 5),
    easeInOutQuint: x => x < 0.5 ? 16 * x * x * x * x * x : 1 - Math.pow(-2 * x + 2, 5) / 2,
    easeInExpo: x => x === 0 ? 0 : Math.pow(2, 10 * x - 10),
    easeOutExpo: x => x === 1 ? 1 : 1 - Math.pow(2, -10 * x),
    easeInOutExpo: x => x === 0 ? 0
                      : x === 1 ? 1
                      : x < 0.5 ? Math.pow(2, 20 * x - 10) / 2
                      : (2 - Math.pow(2, -20 * x + 10)) / 2,
    easeOutBack: x => {
        const c1 = 1.70158;
        const c3 = c1 + 1;
        
        return 1 + c3 * Math.pow(x - 1, 3) + c1 * Math.pow(x - 1, 2);
    },
    easeOutElastic: x => {
        const c4 = (2 * Math.PI) / 3;
        
        return x === 0 ? 0
             : x === 1
             ? 1
             : Math.pow(2, -10 * x) * Math.sin((x * 10 - 0.75) * c4) + 1;
    },
    easeOutBounce: x => {
        const n1 = 7.5625;
        const d1 = 2.75;
        
        if (x < 1 / d1) {
            return n1 * x * x;
        } else if (x < 2 / d1) {
            return n1 * (x -= 1.5 / d1) * x + 0.75;
        } else if (x < 2.5 / d1) {
            return n1 * (x -= 2.25 / d1) * x + 0.9375;
        } else {
            return n1 * (x -= 2.625 / d1) * x + 0.984375;
        }
    },
};

class Anim {
    constructor(speed) {
        this.frame = 0;
        this.speed = speed;
        this.anims = {};
    }

    addAnim(name, val1, val2, f1, f2, easing) {
        this.anims[name] = {
            val1: val1,
            val2: val2,
            f1: f1,
            f2: f2,
            easing: easing
        }
        this.getValue(name);
    }

    getValue(name) {
        let opts = this.anims[name];
        if (this.frame <= opts.f1) {
            return opts.val1;
        } else if (this.frame >= opts.f2) {
            return opts.val2;
        } else {
            return lerp(opts.val1, opts.val2, 
                easings[opts.easing]((this.frame-opts.f1)/(opts.f2-opts.f1)));
        }
    }

    update(amount = 1) {
        this.frame += amount;
    }
}