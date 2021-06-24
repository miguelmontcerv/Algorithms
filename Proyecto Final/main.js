function Point(x, y, g) {
    this.x = x || 0;
    this.y = y || 0;
    this.graphic = g;
    this.main_line = null;
};

Point.prototype.x = null;
Point.prototype.y = null;
Point.prototype.graphic = null;
Point.prototype.main_line = null;

window.onload = function () {
    Raphael.fn.line = function (startX, startY, endX, endY) {
        return this.path('M' + startX + ' ' + startY + ' L' + endX + ' ' + endY);
    };

    var paper = Raphael("canvas", 500, 400);
    var clearbtn = $('#clearbtn');
    var randombtn = $('#randombtn');
    var runbtn = $('#runbtn');
    var points = [];
    var canvas = null;
    var locked = false;
    var convexH = null;
    var auxtimer = null;

    function lineAnim(p, q) {
        line = paper.line(p.x, p.y, p.x, p.y).attr({
            'stroke-linecap': 'round',
            'stroke-linejoin': 'round',
            'stroke': '#23cec5'
        });
        p.main_line = line.animate({
            'stroke-width': '4',
            'path': 'M' + p.x + ' ' + p.y + ' L' + q.x + ' ' + q.y
        }, 1000);
    }

    function lineAnimFin(p, q) {
        line = paper.line(p.x, p.y, p.x, p.y).attr({
            'stroke-linecap': 'round',
            'stroke-linejoin': 'round',
            'stroke': '#FF5733'
        });
        p.main_line = line.animate({
            'stroke-width': '4',
            'path': 'M' + p.x + ' ' + p.y + ' L' + q.x + ' ' + q.y
        }, 1000);
    }


    function updateColorAnim(p) {
        c = paper.circle(p.x, p.y, 1).animate({
            r: 10,
            fill: '#131723',
            "stroke-width": 0
        }, 2000);
    }

    function deleteLineAnim(p) {
        p.main_line.animate({
            'stroke': 'rgba(255, 0, 0, 0.69)',
        }, 4000);
        p.main_line.animate({
            //'stroke': 'rgba(255, 0, 0, 0.69)',
            'stroke-width': '0'
        }, 1000);
    }


    var auxF = {
        lineAnim: lineAnim,
        lineAnimFin: lineAnimFin,
        deleteLineAnim: deleteLineAnim,
        middleLine: middleLine,
        drLine: drLine,
        dlLine: dlLine,
    };

    function getMousePos(e) {
        var totalOffsetX = 0;
        var totalOffsetY = 0;
        var canvasX = 0;
        var canvasY = 0;
        var currentElement = document.getElementById('canvas');

        do {
            totalOffsetX += currentElement.offsetLeft - currentElement.scrollLeft;
            totalOffsetY += currentElement.offsetTop - currentElement.scrollTop;
        }
        while (currentElement = currentElement.offsetParent);

        canvasX = e.pageX - totalOffsetX - document.body.scrollLeft;
        canvasY = e.pageY - totalOffsetY - document.body.scrollTop;

        return new Point(canvasX, canvasY, null, null);
    }

    function addPointAnim(p) {
        if (locked) {
            return;
        }

        if (points.length <= 9) {
            c = paper.circle(p.x, p.y, 1).animate({
                r: 5,
                fill: '#131723',
                "stroke-width": 0
            }, 200);
            p.graphic = c;
            points.push(p);
        } else {
            alert("No se pueden poner mas de 10 puntos")
        }
    }

    function clear() {
        paper.clear();
        canvas = paper.rect(0, 0, 500, 400, 40).attr({
            fill: '#62a8ba',
            stroke: "none"
        });
        points = [];
        unlock();
        running = false;
        convexH = null;
        runbtn.text('Iniciar');
        runbtn.attr('disabled', false);
        $("#group").empty();
        canvas.mouseup(function (e) {
            p = getMousePos(e);
            addPointAnim(p);
        });
    }

    function lock() {
        locked = true;
        if (convexH == null) {
            convexH = new CHAlgorith(points, auxF);
        }
    }

    function unlock() {
        locked = false;
        randombtn.attr('disabled', false);
    }

    function middleLine() {
        line = paper.line(250, 0, 250, 400).attr({
            'stroke-linecap': 'round',
            'stroke-linejoin': 'round',
            'stroke': '#0F365F'
        });
        p.main_line = line.animate({
            'stroke-width': '4',
            'path': 'M' + 250 + ' ' + 0 + ' L' + 250 + ' ' + 400
        }, 1000);
    }

    function drLine(d) {

        x2 = 250 + d;
        text = 250 + d / 2

        line = paper.line(250, 0, x2, 0).attr({
            'stroke-linecap': 'round',
            'stroke-linejoin': 'round',
            'stroke': '#0F365F'
        });
        p.main_line = line.animate({
            'stroke-width': '9',
            'path': 'M' + 250 + ' ' + 0 + ' L' + x2 + ' ' + 0
        }, 1000);

        paper.text(text, 15, "d")
    }

    function dlLine(d) {
        x2 = 250 - d;
        text = 250 - d / 2

        line = paper.line(250, 0, x2, 0).attr({
            'stroke-linecap': 'round',
            'stroke-linejoin': 'round',
            'stroke': '#0F365F'
        });
        line.animate({
            'stroke-width': '9',
            'path': 'M' + 250 + ' ' + 0 + ' L' + x2 + ' ' + 0
        }, 1000);

        paper.text(text, 15, "d")
    }

    function StartPause() {
        if (running) {
            running = false;
            window.clearInterval(auxtimer);
            runbtn.text('Continuar');
            runbtn.attr('disabled', false);
            clearbtn.attr('disabled', false);
        } else {
            running = true;
            lock();
            if (convexH == null) {
                convexH = new CHAlgorith(points, auxF);
            }
            runbtn.text('Pausa');
            clearbtn.attr('disabled', true);
            auxtimer = window.setInterval(function () {
                r = convexH.iterate();
                if (!r) {
                    window.clearInterval(auxtimer);
                    runbtn.text('Terminado');
                    runbtn.attr('disabled', true);
                    clearbtn.attr('disabled', false);
                }
            }, 800);
        }
    }

    clearbtn.click(function () {
        clear();
    });

    runbtn.click(function () {
        StartPause();
    });

    //Da click en el boton clear para lanzar la funcion clear()
    clearbtn.click();
};


function CHAlgorith(points, auxF) {

    this.States = {
        SORTING: 's',
        DIVIDE: 'dv',
        DONE: 'd'
    };


    this.points = points;
    this.auxF = auxF;
    this.state = this.States.SORTING;
    this.p = this.q = this.r = null;
    this.min = 0;
    this.d = 0;
    this.p1 = 0;
    this.p2 = 0;
    this.pares = [];

    this.arraySort = function () {
        this.points = this.points.sort(function (a, b) {
            if (a.x - b.x == 0) {
                return b.y - a.y;
            }
            return a.x - b.x;
        });
    }

    const dist = (p1, p2) => {
        return Math.sqrt((p1.x - p2.x) * (p1.x - p2.x) +
            (p1.y - p2.y) * (p1.y - p2.y)
        );
    }




    const bruteForce = (puntos, n) => {
        this.min = 10000;
        par = [];
        for (let i = 0; i < n; ++i) {
            for (let j = i + 1; j < n; ++j) {
                if (dist(puntos[i], puntos[j]) < this.min) {
                    this.min = dist(puntos[i], puntos[j])
                    this.p1 = puntos[i];
                    this.p2 = puntos[j];
                    par.push(puntos[i]);
                    par.push(puntos[j]);
                    this.pares.push(par);
                    this.par = [];
                    this.d = this.min;
                    this.auxF.lineAnim(this.p1, this.p2);
                    this.addIns("Comparando (x1=" + this.p1.x + " y1=" + this.p1.y + "), (x2=" + this.p2.x + " y2=" + this.p2.y + ")")
                    //this.auxF.deleteLineAnim(this.p1);


                }
            }
        }
        console.log(this.pares)
        return this.min;
    }


    this.closestUtil = (puntos, n) => {


        if (n == 1) {

            return alert("Debes coloar al menos 2 Puntos.")
        }

        if (n <= 3) return bruteForce(puntos, n);

        mid = Math.floor(n / 2);
        midPoint = puntos[mid];



        let dl = this.closestUtil(puntos, mid);
        let dr = this.closestUtil(puntos, n - mid)

        this.d = Math.min(dl, dr);


        let strip = [];
        let j = 0;

        for (const element of puntos) {
            if (Math.abs(element.x - midPoint.x) < this.d) {
                strip[j] = element;
                j++;
            }
        }
        const res = Math.min(this.d, stripClosest(strip, j, this.d));
        return res;

    }

    const stripClosest = (strip, size, d) => {
        let min = d;
        par = [];

        //sort
        this.points = strip;
        this.arraySort();
        strip = this.points;
        for (let i = 0; i < size; ++i) {
            for (let j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
                if (dist(strip[i], strip[j]) < min) {
                    min = dist(strip[i], strip[j])
                    this.p1 = (strip[i]);
                    this.p2 = (strip[j]);
                    par.push(strip[i]);
                    par.push(strip[j]);
                    this.pares.push(par);
                    this.par = [];
                    this.auxF.lineAnim(this.p1, this.p2);
                    this.addIns("Comparando (x1=" + this.p1.x + " y1=" + this.p1.y + "), (x2=" + this.p2.x + " y2=" + this.p2.y + ")")
                }
            }
        }
        return min;
    }
    this.addIns = function (text) {
        var ul = document.getElementById("group");
        var li = document.createElement('li');
        li.appendChild(document.createTextNode(text));
        ul.appendChild(li);
    }

    this.iterate = function () {
        switch (this.state) {
            case this.States.DONE:
                return false;

            case this.States.SORTING:

                this.arraySort();
                this.state = this.States.DIVIDE;

                return this.iterate();

            case this.States.DIVIDE:
                auxF.middleLine();
                this.closestUtil(points, points.length)
                this.auxF.drLine(this.d)
                this.auxF.dlLine(this.d)
                this.auxF.lineAnimFin(this.p1, this.p2)
                this.addIns("Par mas Cercano (x1=" + this.p1.x + " y1=" + this.p1.y + "), (x2=" + this.p2.x + " y2=" + this.p2.y + ")")

                this.state = this.States.DONE;
                return this.iterate();

        }
        return true;
    }
}