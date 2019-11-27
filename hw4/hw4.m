X_MAX = 100;
Y_MAX = 70;

Ax = axes('Position',[0.1,0.1,0.8,0.8],'XLim',[0,X_MAX],'YLim',[0,Y_MAX]);

try
  [X,Y] = ginput(2);
catch
  clear;
  clc;
end
    
    
rectX1 = round(X(1));
rectY1 = round(Y(1));

rectX2 = round(X(2));
rectY2 = round(Y(2));
  
XMin = min(rectX1,rectX2);
XMax = max(rectX1,rectX2);

YMin = min(rectY1,rectY2);
YMax = max(rectY1,rectY2);

height = YMax - YMin;
width = XMax - XMin;

rectColor = [1,0,0];
 
rectangle('Position',[XMin,YMin,width,height],'FaceColor',rectColor);
  
hold on;

%line read
try
  [X,Y] = ginput(2);
catch
  clear;
  clc;
end
    
    
X1 = round(X(1));
Y1 = round(Y(1));

X2 = round(X(2));
Y2 = round(Y(2));

M = zeros(X_MAX,Y_MAX);

color = 1;
colLine = [0,0,1];

Bersenham_Line;

for i = 1 : X_MAX
   for j = 1 : Y_MAX
      if M(i,j) == color
         rectangle('Position',[i-1,j-1,1,1],'FaceColor',colLine);
     end
  end
end  

x1 = X(1);
x2 = X(2);
y1 = Y(1);
y2 = Y(2);

shouldDraw = true;
CohenSuttherLand2DClip;

if(shouldDraw)
    color = 2;
    colLine = [0,1,0];

    X1 = round(x1);
    X2 = round(x2);
    Y1 = round(y1);
    Y2 = round(y2);

    Bersenham_Line;

    pause(2);

    for i = 1 : X_MAX
       for j = 1 : Y_MAX
          if M(i,j) == color
             rectangle('Position',[i-1,j-1,1,1],'FaceColor',colLine);
         end
       end
    end
end  