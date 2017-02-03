#include "main.h"
int main(int argc, char** argv){
	//fd
	int fd = Creat("js/gao.js" , USER_MODE);
	
	//head
	char head[] = "//Author: hd7771\n\n\n";
	Write(fd , head , strlen(head));
	
	//alisa
	char alisa[] = "var loader = PIXI.loader,\n\
	Container = PIXI.Container,\n\
	autoDetectRenderer = PIXI.autoDetectRenderer,\n\
	resources = PIXI.loader.resources,\n\
    fromImage = PIXI.Texture.fromImage,\n\
    Text = PIXI.Text,\n\
    Sprite = PIXI.Sprite,\n\
    Graphics = PIXI.Graphics,\n\
    TextureCache = PIXI.utils.TextureCache,\n\
    fromVideo = PIXI.VideoBaseTexture.fromUrls,\n\
    VideoBaseTexture = PIXI.VideoBaseTexture;\n";
    Write(fd , alisa , strlen(alisa));
    
    //game and dialog
    //char settings[] = "var game_width = 1280 , game_height = 720 , dialog_width = 1280 , dialog_height = 185;"
    char settings1[] = "var game_width = ";
    char settings2[] = " , game_height = ";
    char settings3[] = " , dialog_width = ";
    char settings4[] = " , dialog_height = ";
    char num1[10]; itoa(game_width , num1);
    char num2[10]; itoa(game_height , num2);
    char num3[10]; itoa(dialog_width , num3);
    char num4[10]; itoa(dialog_height , num4);
    char settingsEnd[] = ";\n";
    Write(fd , settings1 , strlen(settings1));
    Write(fd , num1 , strlen(num1));
    Write(fd , settings2 , strlen(settings2));
    Write(fd , num2 , strlen(num2));
    Write(fd , settings3 , strlen(settings3));
    Write(fd , num3 , strlen(num3));
    Write(fd , settings4 , strlen(settings4));
    Write(fd , num4 , strlen(num4));
    Write(fd , settingsEnd , strlen(settingsEnd));
    
    //renderer
    char renderer[] = "var renderer = PIXI.autoDetectRenderer(game_width, game_height, { antialias: true } , {backgroundColor : 0x1099bb} , { transparent: true });\n";
    Write(fd , renderer , strlen(renderer));
    
    //DOM
	char dom[] = "//DOM\n\
var gameArea = document.getElementById(\"gameArea\");\n\
	gameArea.appendChild(renderer.view);\n\
	$('#gameArea').bind('contextmenu', function(e){\n\
		return false;\n\
	});\n";
	Write(fd , dom , strlen(dom));
	
	char sprite[] = "// create the root of the scene graph\n\
var stage = new Container();\n\
stage.interactive = true;\n\
\n\
\n\
// CG or BG\n\
var bgSprite = new Sprite();\n\
bgSprite.width = game_width;\n\
bgSprite.height = game_height;\n\
bgSprite.interactive = true;\n\
\n\
\n\
// dialog\n\
var graphics = new PIXI.Graphics();\n\
graphics.lineStyle(2, 0xFF00FF, 1);\n\
graphics.beginFill(0xFF00BB, 0.5);\n\
graphics.drawRoundedRect(0, game_height - dialog_height, dialog_width, dialog_height, 15);\n\
graphics.endFill();\n\
graphics.interactive = true;\n\
\n\
\n\
//Text\n\
//text_style\n\
var style = {\n\
    fontFamily : 'Arial',\n\
    fontSize : '26px',\n\
    fill : '#F7EDCA',\n\
    stroke : '#4a1850',\n\
    strokeThickness : 5,\n\
    dropShadow : true,\n\
    dropShadowColor : '#000000',\n\
    dropShadowAngle : Math.PI / 6,\n\
    dropShadowDistance : 0,\n\
    wordWrap : true,\n\
    wordWrapWidth : 440\n\
};\n\
style.fontSize = 26 + 'px';\n\
//person_name\n\
var person = new Text('' , style);\n\
person.x = game_width / 6;\n\
person.y = game_height - dialog_height;\n\
//word\n\
var word = new Text('' , style);\n\
word.x = person.x + 30;\n\
word.y = person.y + 40;\n\
\n\
\n\
//character\n\
var leftCharacter , middleCharacter , rightCharacter;\n\
var leftCharacterSprite = new Sprite();\n\
var middleCharacterSprite = new Sprite();\n\
var rightCharacterSprite = new Sprite();\n\
\n\
//video\n\
//var vtexture = new VideoBaseTexture();\n\
//var vvtexture = new PIXI.Texture();\n\
var vsprite = new Sprite();\n\
vsprite.width = game_width;\n\
vsprite.height = game_height;\n\
\n\
//control layerr\n\
var clickControl = new PIXI.Graphics();\n\
clickControl.lineStyle(2, 0xFF00FF, 1);\n\
clickControl.beginFill(0xFF00BB, 0);\n\
clickControl.drawRoundedRect(0, 0, game_width, game_height, 15);\n\
clickControl.endFill();\n\
clickControl.interactive = true;\n\
clickControl.on('mousedown' , onDown);\n\
clickControl.on('touchstart' , onDown);\n\
clickControl.on('rightdown' , onRight);\n\
var cur = 0;\n\
var opBg = new Array();\n\
var opPerson = new Array();\n\
var opWord = new Array();\n\
var opLeftCharacter = new Array();\n";
	Write(fd , sprite , strlen(sprite));
	
	std::vector<std::string> opBg , opPerson , opWord , opLeftCharacter;
	std::string nBg , nPerson , nWord , nLeftCharacter;
	int sfd = open("test.txt" , RWX , USER_MODE);
	while(1){
		int len = Read(sfd , readBuffer);
		if(len == 0) break;
		if(readBuffer[0] == 'l'){
			if(strcmp((readBuffer + 5) , "clear") == 0){
				nLeftCharacter = "clear";
			}
			else{
				dotc(readBuffer);
				nLeftCharacter = "char" + ctos(readBuffer + 4);
			}
		}
		else if(readBuffer[0] == 'b'){
			dotc(readBuffer);
			nBg = ctos(readBuffer);
		}
		else if(readBuffer[0] == 'd'){
			int i;
			for(i = 8 ; ; ++ i){
				if(readBuffer[i] == '"') break;
				else nPerson += readBuffer[i];
			}
			i += 3;
			for( ; ; ++ i){
				if(readBuffer[i] == '"') break;
				else nWord += readBuffer[i];
			}
			if(nPerson.size() != 0){
				nPerson = "【" + nPerson + "】";
			}
			if(nWord.size() != 0){
				nWord = "「 " + nWord + " 」";
			}
		}
		else if(readBuffer[0] == 'c'){
			opBg.push_back(nBg);
			opPerson.push_back(nPerson);
			opWord.push_back(nWord);
			opLeftCharacter.push_back(nLeftCharacter);
			nBg.clear();
			nLeftCharacter.clear();
			nPerson.clear();
			nWord.clear();
		}
	}
	int end = opBg.size();
	for(int i = 0 ; i < end ; ++ i){
		char num[100];
		itoa(i , num);	
		
		nBg = "opBg[" + ctos(num) + "] = " + "'" + opBg[i] + "';\n";
		
		nPerson = "opPerson[" + ctos(num) + "] = " + "'" + opPerson[i] + "';\n";
		
		nWord = "opWord[" + ctos(num) + "] = " + "'" + opWord[i] + "';\n";
		
		nLeftCharacter = "opLeftCharacter[" + ctos(num) + "] = " + "'" + opLeftCharacter[i] + "';\n";
		
		//std::cout<<"---"<<i<<"---"<<std::endl;
		//std::cout<<nBg<<std::endl;
		//std::cout<<nPerson<<std::endl;
		//std::cout<<nWord<<std::endl;
		//std::cout<<nLeftCharacter<<std::endl;
		
		char cnBg[256] , cnPerson[256] , cnWord[256] , cnLeftCharacter[256];
		stoc(nBg , cnBg);stoc(nPerson , cnPerson);
		stoc(nWord , cnWord);stoc(nLeftCharacter , cnLeftCharacter);
		
		if(nBg.size() != 0) Write(fd , cnBg , strlen(cnBg));
		Write(fd , cnPerson , strlen(cnPerson));
		Write(fd , cnWord , strlen(cnWord));
		Write(fd , cnLeftCharacter , strlen(cnLeftCharacter));
	}
	
	char cend[128];
	itoa(end , cend);
	std::string tmp;
	tmp += "var end = " + ctos(cend) + ";\n";
	stoc(tmp , cend);
	Write(fd , cend , strlen(cend));
	
	char fin[] = "var vtexture = vsprite.texture.baseTexture;\n\
function onDown(eventData){\n\
	if(vtexture.source == null || vtexture.source.ended == true){\n\
		if(person.visible == false){\n\
			person.visible = true;\n\
			word.visible = true;\n\
			graphics.visible = true;\n\
		}\n\
		else{\n\
			if(cur < end){\n\
				if(opBg[cur] != '') bgSprite.texture = fromImage(opBg[cur]);\n\
				\n\
				person.text = opPerson[cur];\n\
				\n\
				word.text = opWord[cur];\n\
				\n\
				if(opLeftCharacter[cur] == \"clear\") leftCharacterSprite.visible = false;\n\
				else if(opLeftCharacter[cur] != ''){\n\
					leftCharacterSprite.visible = true;\n\
					leftCharacterSprite.texture = fromImage(opLeftCharacter[cur]);\n\
				}\n\
				\n\
				cur ++;\n\
			}\n\
			else{\n\
				\n\
			}\n\
		}\n\
	}\n\
}\n\
\n\
function onRight(eventData){\n\
	if(vtexture.source == null || vtexture.source.ended == true){\n\
		if(person.visible == true){\n\
			person.visible = false;\n\
			word.visible = false;\n\
			graphics.visible = false;\n\
		}\n\
		else{\n\
			person.visible = true;\n\
			word.visible = true;\n\
			graphics.visible = true;\n\
		}\n\
	}\n\
}\n\
\n\
\n\
// add childs to stage\n\
stage.addChild(bgSprite);\n\
stage.addChild(leftCharacterSprite);\n\
stage.addChild(graphics);\n\
stage.addChild(person);\n\
stage.addChild(word);\n\
stage.addChild(vsprite);\n\
stage.addChild(clickControl)\n\
\n\
\n\
// run the render loop\n\
animate();\n\
function animate() {\n\
    renderer.render(stage);\n\
    if(vtexture.source == null || vtexture.source.ended == true) vsprite.visible = false;\n\
    requestAnimationFrame( animate );\n\
}\n";
	Write(fd , fin , strlen(fin));
	return 0;
}

