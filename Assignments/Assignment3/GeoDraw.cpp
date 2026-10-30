/********************************************************************************************
 GeoDraw Version 1.0 (26.08) - Last revision: 25/08/2026
 Author: Conor McArdle
 - A simple C/C++ 2D drawing library that outputs drawings as JavaScript
 - Includes a simplified C function interface
 - Generated animations include automatic play/pause and timeline controls

 NOTICE: Copyright (C) 2023-2026 Conor McArdle, Dublin City University - All Rights Reserved.
 Permission is granted to students registered for DCU modules EEN1091 and EEN1092
 to use this code for their personal use only. No permission is granted to share this file
 by any means, including but not limited to, uploading it or submitting it to any private
 or public server on the Web/Internet or any online service which publishes or otherwise
 processes or stores uploaded content. This notice must stay attached to this file.
*********************************************************************************************/

#include "GeoDraw.h"

namespace GeoDraw
{

const string _gd_version = "26.08";  // software version number

string _gd_html_pre;                 // html to appear before canvas element
string _gd_html_post;                // html to appear after canvas element

string gd_to_string(int a)           // utility string conversion methods
{
    char buffer[50];
    sprintf(buffer, "%d", a);
    return string(buffer);
}
string gd_to_string(unsigned int a)
{
    return gd_to_string((int)a);
}
string gd_to_string(double a, unsigned short decimalPlaces)
{
    char buffer[50];
    string format = "%." + gd_to_string(decimalPlaces) + "f";
    sprintf(buffer, format.c_str(), a);
    return string(buffer);
}

/********************************************************************************************
 Canvas class - public methods - Canvas::draw() and Canvas::draw(filename)
*********************************************************************************************/

void Canvas::draw() {
    string JSDrawingString;

    // HTML output file header, compact drawing helper functions and animation controls
    JSDrawingString += "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>GeoDraw</title>\n";
    JSDrawingString += "<style>\n";
    JSDrawingString += "  canvas { border:1px solid #505050; display:block; }\n";
    JSDrawingString += "  #gdControls { width:" + gd_to_string((int)_xDim) + "px; display:none; align-items:center; gap:10px; margin:10px 0 10px 0; font-family:Arial,sans-serif; color:#d0d0d0; }\n";
    JSDrawingString += "  #gdPlayPause { min-width:64px; background-color:#404040; color:#d0d0d0; border:1px solid #707070; border-radius:4px; padding:4px 10px; }\n";
    JSDrawingString += "  #gdSlider { flex:1; appearance:none; -webkit-appearance:none; background:transparent; }\n";
    JSDrawingString += "  #gdSlider::-webkit-slider-runnable-track { height:6px; background:#707070; border-radius:3px; }\n";
    JSDrawingString += "  #gdSlider::-webkit-slider-thumb { -webkit-appearance:none; width:14px; height:14px; margin-top:-4px; background:#909090; border:1px solid #505050; border-radius:50%; }\n";
    JSDrawingString += "  #gdSlider::-moz-range-track { height:6px; background:#707070; border-radius:3px; }\n";
    JSDrawingString += "  #gdSlider::-moz-range-progress { height:6px; background:#505050; border-radius:3px; }\n";
    JSDrawingString += "  #gdSlider::-moz-range-thumb { width:14px; height:14px; background:#909090; border:1px solid #505050; border-radius:50%; }\n";
    JSDrawingString += "</style>\n<script>\n\n";

    JSDrawingString += "window.onload=function(){\n";
    JSDrawingString += "const canvas=document.getElementById('myCanvas'),ctx=canvas.getContext('2d');\n";

    // Short JavaScript helper functions keep repeated drawing commands out of every frame (reduces overall output file size)
    JSDrawingString += "const gdRGB=c=>'rgb'+c;\n";
    JSDrawingString += "function gdBg(c){ctx.fillStyle=gdRGB(c);ctx.fillRect(0,0,canvas.width,canvas.height);}\n";
    JSDrawingString += "function gdPt(x,y,r,c){ctx.beginPath();ctx.fillStyle=gdRGB(c);ctx.arc(x,y,r,0,2*Math.PI);ctx.fill();}\n";
    JSDrawingString += "function gdLn(x1,y1,x2,y2,c,w){ctx.beginPath();ctx.strokeStyle=gdRGB(c);ctx.lineWidth=w;ctx.moveTo(x1,y1);ctx.lineTo(x2,y2);ctx.stroke();}\n";
    JSDrawingString += "function gdCi(x,y,r,c,w,f){ctx.beginPath();if(f)ctx.fillStyle=gdRGB(c);else{ctx.strokeStyle=gdRGB(c);ctx.lineWidth=w;}ctx.arc(x,y,r,0,2*Math.PI);f?ctx.fill():ctx.stroke();}\n";
    JSDrawingString += "function gdPo(v,c,w,f){if(!v.length)return;ctx.beginPath();if(f)ctx.fillStyle=gdRGB(c);else{ctx.strokeStyle=gdRGB(c);ctx.lineWidth=w;}ctx.moveTo(v[0],v[1]);for(let i=2;i<v.length;i+=2)ctx.lineTo(v[i],v[i+1]);ctx.closePath();f?ctx.fill():ctx.stroke();}\n";
    JSDrawingString += "function gdTx(t,x,y,font,size,align,c,f){ctx.font=size+'px '+font;ctx.textAlign=align;ctx.textBaseline='middle';if(f){ctx.fillStyle=gdRGB(c);ctx.fillText(t,x,y);}else{ctx.strokeStyle=gdRGB(c);ctx.strokeText(t,x,y);}}\n";
    JSDrawingString += "gdBg('" + bg_color.to24BitColorString() + "');\n\n";

    // Generate JavaScript frame functions and pause durations
    cout << "Generating " << elements.size() << " JavaScript drawing objects ... ";
    clock_t start, end;
    start = clock();
    JSDrawingString += this->generateJSDrawingString();
    end = clock();
    cout << "done in ";
    cout << double(end - start)/double(CLOCKS_PER_SEC) << " seconds." << endl;

    // Playback and slider logic
    JSDrawingString += "\nlet gdCurrent=0,gdPlaying=false,gdTimer=null;\n";
    JSDrawingString += "const gdControls=document.getElementById('gdControls'),gdSlider=document.getElementById('gdSlider'),gdButton=document.getElementById('gdPlayPause');\n";
    JSDrawingString += "function gdUpdateUI(){if(gdFrames.length<2)return;gdSlider.value=gdCurrent;gdButton.textContent=gdPlaying?'Pause':'Play';}\n";
    JSDrawingString += "function gdStop(){gdPlaying=false;if(gdTimer!==null){clearTimeout(gdTimer);gdTimer=null;}gdUpdateUI();}\n";
    JSDrawingString += "function gdShow(n){gdStop();gdBg('" + bg_color.to24BitColorString() + "');gdCurrent=Math.max(0,Math.min(n,gdFrames.length-1));for(let i=0;i<=gdCurrent;i++)gdFrames[i]();gdUpdateUI();}\n";
    JSDrawingString += "function gdNext(){if(!gdPlaying)return;if(gdCurrent>=gdFrames.length-1){gdStop();return;}gdCurrent++;gdFrames[gdCurrent]();gdUpdateUI();if(gdCurrent>=gdFrames.length-1){gdStop();return;}gdTimer=setTimeout(gdNext,gdDelay[gdCurrent]);}\n";
    JSDrawingString += "function gdPlay(){if(gdFrames.length<2)return;if(gdCurrent>=gdFrames.length-1)gdShow(0);gdPlaying=true;gdUpdateUI();gdTimer=setTimeout(gdNext,gdDelay[gdCurrent]);}\n";
    JSDrawingString += "if(gdFrames.length){gdFrames[0]();gdUpdateUI();}\n";
    JSDrawingString += "if(gdFrames.length>1){gdSlider.max=gdFrames.length-1;gdControls.style.display='flex';gdSlider.oninput=function(){gdShow(Number(this.value));};gdButton.onclick=function(){gdPlaying?gdStop():gdPlay();};gdPlay();}\n";

    // HTML output file footer
    JSDrawingString += "\n};\n</script>\n</head>\n";
    JSDrawingString += "<body style=\"background-color:#404040;\">\n";
    JSDrawingString += _gd_html_pre;
    JSDrawingString += "  <canvas id=\"myCanvas\" width=\"" + gd_to_string((int)_xDim) + "\" height=\"" + gd_to_string((int)_yDim) + "\"></canvas>\n";
    JSDrawingString += "  <div id=\"gdControls\"><button id=\"gdPlayPause\" type=\"button\">Pause</button><input id=\"gdSlider\" type=\"range\" min=\"0\" value=\"0\" step=\"1\"></div>\n";
    JSDrawingString += "<p style=\"font-family:Arial;font-size:10px;color:Gray\"><br>&nbsp;Produced by GeoDraw-" + _gd_version + " C/C++ Library. Author: Conor.McArdle@dcu.ie, 2026</p>";
    JSDrawingString += _gd_html_post;
    JSDrawingString += "</body>\n</html>\n";

    // Save the JS string to file
    std::ofstream outHTMLFile;
    outHTMLFile.open(outFileName.c_str());
    if(outHTMLFile) {
        cout << "Saving to file ... ";
        outHTMLFile << JSDrawingString;
        outHTMLFile.close();
        cout << "done." << endl;
        cout << "JavaScript drawing created in " << outFileName << endl;
    } else {
        cerr << "Error opening output file " << outFileName << endl;
    }
}

void Canvas::draw(string filename) {
    outFileName = filename;
    Canvas::draw();
}

/********************************************************************************************
 Canvas class - private helper members
*********************************************************************************************/

string Canvas::generateJSDrawingString() {
    string JS;
    string frame;
    vector<u_int> delays;
    bool firstFrame = true;

    JS += "const gdFrames=[\n";

    for (u_int i=0; i<elements.size(); i++) {
        frame += elements[i]->toJavaScript();

        if (elements[i]->pauseAfter != 0) {
            if (!firstFrame) JS += ",\n";
            JS += "function(){" + frame + "}";
            firstFrame = false;
            delays.push_back(elements[i]->pauseAfter);
            frame.clear();
        }
    }

    // Commands after the final pause still form a final displayable frame.
    // With no pause at all, the whole drawing is represented by one frame.
    if (!frame.empty() || firstFrame) {
        if (!firstFrame) JS += ",\n";
        JS += "function(){" + frame + "}";
        delays.push_back(0);
    }

    JS += "\n];\nconst gdDelay=[";
    for (u_int i=0; i<delays.size(); i++) {
        if (i > 0) JS += ",";
        JS += gd_to_string(delays[i]);
    }
    JS += "];\n";
    return JS;
}


/********************************************************************************************
 JavaScript drawing implementations for Drawable objects
*********************************************************************************************/

/********************************************************************************************
 Point::toJavaScript() - private
 A friend of the Canvas class
 Called by Canvas::draw() to generate JavaScript to draw a Point object

 02.02.2025 Issue: pen width of 1 rounding down to 0 radius. Correction: cast with (double), not (int)

*********************************************************************************************/
string Point::toJavaScript() const {
    return "gdPt(" + gd_to_string(coord.x()) + "," + gd_to_string(coord.y()) + "," +
           gd_to_string((double)penWidth/2) + ",'" + color.to24BitColorString() + "');";
}

/********************************************************************************************
 LineSeg::toJavaScript() - private
 A friend of the Canvas class
 Called by Canvas::draw() to generate JavaScript to draw a LineSeg object
*********************************************************************************************/
string LineSeg::toJavaScript() const {
    return "gdLn(" + gd_to_string(c1.x()) + "," + gd_to_string(c1.y()) + "," +
           gd_to_string(c2.x()) + "," + gd_to_string(c2.y()) + ",'" +
           color.to24BitColorString() + "'," + gd_to_string((int)penWidth) + ");";
}

/********************************************************************************************
 Circle::toJavaScript() - private
 A friend of the Canvas class
 Called by Canvas::draw() to generate JavaScript to draw a Circle object
*********************************************************************************************/
string Circle::toJavaScript() const {
    return "gdCi(" + gd_to_string(cen.x()) + "," + gd_to_string(cen.y()) + "," +
           gd_to_string(radius) + ",'" + color.to24BitColorString() + "'," +
           gd_to_string((int)penWidth) + "," + (fillState == FILLED ? "1" : "0") + ");";
}

/********************************************************************************************
 Polygon::toJavaScript() - private
 A friend of the Canvas class
 Called by Canvas::draw() to generate JavaScript to draw a Polygon object
*********************************************************************************************/
string Polygon::toJavaScript() const {
    if (vertices.size() == 0) return "";
    string JS_string = "gdPo([";
    for (u_int i=0; i<vertices.size(); i++) {
        if (i > 0) JS_string += ",";
        JS_string += gd_to_string(vertices[i].x()) + "," + gd_to_string(vertices[i].y());
    }
    JS_string += "],'" + color.to24BitColorString() + "'," + gd_to_string((int)penWidth) + ",";
    JS_string += (fillState == FILLED ? "1" : "0");
    JS_string += ");";
    return JS_string;
}

/********************************************************************************************
 Text::toJavaScript() - private
 A friend of the Canvas class
 Called by Canvas::draw() to generate JavaScript to draw Text on canvas
*********************************************************************************************/
string Text::toJavaScript() const {
    string font_name;
    switch (this->font) {
        case Arial: font_name = "Arial"; break;
        case Courier: font_name = "Courier"; break;
        case Times: font_name = "Times"; break;
    }

    string align_name;
    if (alignment == LEFT) align_name = "left";
    else if (alignment == CENTER) align_name = "center";
    else align_name = "right";

    // Escape characters that have special meaning in a JavaScript single-quoted string.
    string escaped;
    for (u_int i=0; i<text.size(); i++) {
        char ch = text[i];
        if (ch == '\\') escaped += "\\\\";
        else if (ch == '\'') escaped += "\\'";
        else if (ch == '\n') escaped += "\\n";
        else if (ch == '\r') escaped += "\\r";
        else escaped += ch;
    }

    return "gdTx('" + escaped + "'," + gd_to_string(position.x()) + "," +
           gd_to_string(position.y()) + ",'" + font_name + "'," +
           gd_to_string((int)fontSize) + ",'" + align_name + "','" +
           color.to24BitColorString() + "'," + (fillState == FILLED ? "1" : "0") + ");";
}

} // end GeoDraw namespace


/********************************************************************************************
*
*   SIMPLIFIED C-STYLE INTERFACE for GeoDraw - Implementation
*
********************************************************************************************/

namespace GeoDrawC
{
    u_int       _cgd_canvas_size_x   =   600;
    u_int       _cgd_canvas_size_y   =   600;
    u_int       _cgd_pen_width       =   2;
    Color       _cgd_pen_color       =   BLACK;
    Color       _cgd_fill_color      =   GRAY;
    Font        _cgd_font            =   Arial;
    u_int       _cgd_font_size       =   20;
    Color       _cgd_font_color      =   BLACK;
    TextAlign   _cgd_text_alignment  =   LEFT;
    Canvas      _cgd_canvas(_cgd_canvas_size_x,_cgd_canvas_size_y);
}

u_int gd_getCanvasSizeX() {
    return GeoDrawC::_cgd_canvas.xDim();
}

u_int gd_getCanvasSizeY() {
    return GeoDrawC::_cgd_canvas.yDim();
}

void gd_resetCanvasSize(u_int xSize, u_int ySize) {
    GeoDrawC::_cgd_canvas.reset(xSize, ySize);
}

void gd_setCanvasColor(Color color) {
    GeoDrawC::_cgd_canvas.setBackgroundColor(color);
}

void gd_setCanvasColor(double r, double g, double b) {
    GeoDrawC::_cgd_canvas.setBackgroundColor(Color(r,g,b));
}

void gd_setPenWidth(u_int width) {
    GeoDrawC::_cgd_pen_width = (width > 0) ? width : 1;
}

void gd_setPenColor(Color color) {
    GeoDrawC::_cgd_pen_color = color;
}

void gd_setPenColor(double r, double g, double b) {
    GeoDrawC::_cgd_pen_color = Color(r,g,b);
}

void gd_setFillColor(Color color) {
    GeoDrawC::_cgd_fill_color = color;
}

void gd_setFillColor(double r, double g, double b) {
    GeoDrawC::_cgd_fill_color = Color(r,g,b);
}

void gd_setFont(Font font) {
    GeoDrawC::_cgd_font = font;
}

void gd_setTextSize(u_int font_size) {
    GeoDrawC::_cgd_font_size = font_size;
}

void gd_setTextColor(Color color) {
    GeoDrawC::_cgd_font_color = color;
}

void gd_setTextColor(double r, double g, double b) {
    GeoDrawC::_cgd_font_color = Color(r,g,b);
}

void gd_setTextAlignment(TextAlign alignment) {
    GeoDrawC::_cgd_text_alignment = alignment;
}

void gd_point(double x, double y) {
    GeoDrawC::_cgd_canvas.add(Point(x,y), GeoDrawC::_cgd_pen_color, GeoDrawC::_cgd_pen_width);
}

void gd_line(double x1, double y1, double x2, double y2) {
    GeoDrawC::_cgd_canvas.add(LineSeg(x1,y1,x2,y2), GeoDrawC::_cgd_pen_color, GeoDrawC::_cgd_pen_width);
}

void gd_circle(double x, double y, double radius) {
    GeoDrawC::_cgd_canvas.add(Circle(x,y,radius), GeoDrawC::_cgd_pen_color, GeoDrawC::_cgd_pen_width);
}

void gd_circleFilled(double x, double y, double radius) {
    GeoDrawC::_cgd_canvas.add(Circle(x,y,radius), GeoDrawC::_cgd_fill_color, FILLED);
}

void gd_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    Polygon poly;
    poly.add(x1,y1);
    poly.add(x2,y2);
    poly.add(x3,y3);
    GeoDrawC::_cgd_canvas.add(poly, GeoDrawC::_cgd_pen_color, GeoDrawC::_cgd_pen_width);
}

void gd_triangleFilled(double x1, double y1, double x2, double y2, double x3, double y3) {
    Polygon poly;
    poly.add(x1,y1);
    poly.add(x2,y2);
    poly.add(x3,y3);
    GeoDrawC::_cgd_canvas.add(poly, GeoDrawC::_cgd_fill_color, FILLED);
}

void gd_quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    Polygon poly;
    poly.add(x1,y1);
    poly.add(x2,y2);
    poly.add(x3,y3);
    poly.add(x4,y4);
    GeoDrawC::_cgd_canvas.add(poly, GeoDrawC::_cgd_pen_color, GeoDrawC::_cgd_pen_width);
}

void gd_quadFilled(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    Polygon poly;
    poly.add(x1,y1);
    poly.add(x2,y2);
    poly.add(x3,y3);
    poly.add(x4,y4);
    GeoDrawC::_cgd_canvas.add(poly, GeoDrawC::_cgd_fill_color, FILLED);
}

void gd_text(string txt, double x, double y) {
    GeoDrawC::_cgd_canvas.add(Text(txt, x, y, GeoDrawC::_cgd_font, GeoDrawC::_cgd_font_size, GeoDrawC::_cgd_text_alignment), GeoDrawC::_cgd_font_color, FILLED);
}

void gd_pause(u_int pauseTimeMs) {
    GeoDrawC::_cgd_canvas.pause(pauseTimeMs);
}

void gd_clear() {
    GeoDrawC::_cgd_canvas.clear();
}

void gd_save(string filename) {
    GeoDrawC::_cgd_canvas.draw(filename);
}

///////////////////////////////////////////////////////////
