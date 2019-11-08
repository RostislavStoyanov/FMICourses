function [M] = colorRound(x,y,colorAround,M,MaxX,MaxY)
    M = colorIfNotColored((x-1),(y-1),colorAround,M,MaxX,MaxY);
    M = colorIfNotColored((x-1),y,colorAround,M,MaxX,MaxY);
    M = colorIfNotColored((x-1),(y+1),colorAround,M,MaxX,MaxY);
    M = colorIfNotColored(x,(y-1),colorAround,M,MaxX,MaxY);
    M = colorIfNotColored(x,(y+1),colorAround,M,MaxX,MaxY);
    M = colorIfNotColored((x+1),(y-1),colorAround,M,MaxX,MaxY);
    M = colorIfNotColored((x+1),y,colorAround,M,MaxX,MaxY);
    M = colorIfNotColored((x+1),(y+1),colorAround,M,MaxX,MaxY);
end

function [M] = colorIfNotColored(x,y,colorAround,M,MaxX,MaxY)
    if(x > 0 && x <= MaxX && y > 0 && y <= MaxY && M(x,y) == 0)
        M(x,y) = colorAround; 
    end
end