//Author: hd7771

#include "main.h"

std::vector<Vstr> Vtree[1000000];
int cur = 0 , top = 0;
int Stack[1000000];
int bracket[1000000];
Vstr init;


void dfs(Vstr now , int fd){
	handle(now , fd);
	for(int i = 0 ; i < (int)Vtree[stoi(now["index"])].size() ; ++ i){
		Vstr nxt = Vtree[stoi(now["index"])][i];
		connect(now , nxt , fd);
		dfs(nxt , fd);
	}
}

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
graphics.drawRoundedRect(5, game_height - dialog_height, dialog_width - 10 , dialog_height - 5 , 15);\n\
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
var word = new Text('click' , style);\n\
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
//option layer\n\
var option1 = new PIXI.Graphics();\n\
option1.lineStyle(2, 0xFF00FF, 1);\n\
option1.beginFill(0xFF00BB, 0.5);\n\
option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);\n\
option1.endFill();\n\
option1.interactive = true;\n\
var option1_text = new Text('ass we can!!' , style);\n\
option1_text.anchor.set(0.5 , 0.5);\n\
option1_text.position.x = game_width / 2;\n\
option1_text.position.y = game_height / 36 * 7;\n\
option1_text.interactive = true;\n\
//option1.visible = false;\n\
//option1_text.visible = false;\n\
var option1Control = new PIXI.Graphics();\n\
option1Control.lineStyle(2, 0xFF00FF, 1);\n\
option1Control.beginFill(0xFF00BB, 0);\n\
option1Control.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);\n\
option1Control.endFill();\n\
option1Control.interactive = true;\n\
\n\
\n\
\n\
var option2 = new PIXI.Graphics();\n\
option2.lineStyle(2, 0xFF00FF, 1);\n\
option2.beginFill(0xFF00BB, 0.5);\n\
option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);\n\
option2.endFill();\n\
option2.interactive = true;\n\
var option2_text = new Text('ass we can!!' , style);\n\
option2_text.anchor.set(0.5 , 0.5);\n\
option2_text.position.x = game_width / 2;\n\
option2_text.position.y = game_height / 36 * 10;\n\
option2_text.interactive = true;\n\
//option2.visible = false;\n\
//option2_text.visible = false;\n\
var option2Control = new PIXI.Graphics();\n\
option2Control.lineStyle(2, 0xFF00FF, 1);\n\
option2Control.beginFill(0xFF00BB, 0);\n\
option2Control.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);\n\
option2Control.endFill();\n\
option2Control.interactive = true;\n\
\n\
\n\
\n\
option1Control.on('mouseover' , onButtonOver1).on('mouseout', onButtonOut1).on('mousedown', onButtonDown1);\n\
option2Control.on('mouseover' , onButtonOver2).on('mouseout', onButtonOut2).on('mousedown', onButtonDown2);\n\
var flag1 , flag2;\n\
var opFlag = new Array();\n\
\n\
\n\
\n\
function onButtonOver1()\n\
{\n\
	if(option1.visible == false) return;\n\
	option1.clear();\n\
	option1.lineStyle(2, 0x000000, 1);\n\
	option1.beginFill(0x66ccff, 0.5);\n\
	option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);\n\
	option1.endFill();\n\
}\n\
\n\
function onButtonOut1()\n\
{\n\
	if(option1.visible == false) return;\n\
	option1.clear();\n\
	option1.lineStyle(2, 0xFF00FF, 1);\n\
	option1.beginFill(0xFF00BB, 0.5);\n\
	option1.drawRoundedRect(game_width / 4 , game_height / 6 , game_width / 2 , game_height / 18 , 30);\n\
	option1.endFill();\n\
}\n\
\n\
function onButtonOver2()\n\
{\n\
	if(option2.visible == false) return;\n\
	option2.clear();\n\
	option2.lineStyle(2, 0x000000, 1);\n\
	option2.beginFill(0x66ccff, 0.5);\n\
	option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);\n\
	option2.endFill();\n\
}\n\
\n\
function onButtonOut2()\n\
{\n\
	if(option2.visible == false) return;\n\
	option2.clear();\n\
	option2.lineStyle(2, 0xFF00FF, 1);\n\
	option2.beginFill(0xFF00BB, 0.5);\n\
	option2.drawRoundedRect(game_width / 4 , game_height / 6 + game_height / 18 + game_height / 36 , game_width / 2 , game_height / 18 , 30);\n\
	option2.endFill();\n\
}\n\
\n\
function option_visible(val){\n\
	option1.visible = val;\n\
	option2.visible = val;\n\
	option1_text.visible = val;\n\
	option2_text.visible = val;\n\
	option1Control.visible = val;\n\
	option2Control.visible = val;\n\
}\n\
option_visible(false);\n\
\n\
function onButtonDown1()\n\
{\n\
	option_visible(false);\n\
	opFlag[flag1] = true;\n\
	while(gaoStack[gaoCur - 1] == undefined) gaoCur --;\n\
	if(gaoCur != 0) gaoStack[gaoCur - 1].next();\n\
}\n\
\n\
function onButtonDown2()\n\
{\n\
	option_visible(false);\n\
	opFlag[flag2] = true;\n\
	while(gaoStack[gaoCur - 1] == undefined) gaoCur --;\n\
	if(gaoCur != 0) gaoStack[gaoCur - 1].next();\n\
}\n\
\n\
\n\
var Vtree = new Array();\n";
	Write(fd , sprite , strlen(sprite));
	
	int sfd = open("test.txt" , RWX , USER_MODE);
	std::vector<std::string> opBg , opPerson , opWord , opLeftCharacter;
	std::string nBg , nPerson , nWord , nLeftCharacter;
	init["index"] = itos(++ cur);
	init["type"] = "init";
	Stack[top ++] = cur;
	while(1){
		int len = Read(sfd , readBuffer);
		preload(readBuffer);
		std::string sentense = ctos(readBuffer);
		if(len == 0) break;
		if(strncmp(readBuffer , "left" , 4) == 0){
			if(strncmp((readBuffer + 5) , "clear" , 5) == 0){
				nLeftCharacter = "clear";
			}
			else{
				dotc(readBuffer);
				nLeftCharacter = "char" + ctos(readBuffer + 4);
			}
			Nstr nxt;
			nxt["type"] = "left";
			nxt["value"] = nLeftCharacter;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "middle" , 6) == 0){
			if(strncmp((readBuffer + 7) , "clear" , 5) == 0){
				nLeftCharacter = "clear";
			}
			else{
				dotc(readBuffer);
				nLeftCharacter = "char" + ctos(readBuffer + 6);
			}
			Nstr nxt;
			nxt["type"] = "middle";
			nxt["value"] = nLeftCharacter;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "right" , 5) == 0){
			if(strncmp((readBuffer + 6) , "clear" , 5) == 0){
				nLeftCharacter = "clear";
			}
			else{
				dotc(readBuffer);
				nLeftCharacter = "char" + ctos(readBuffer + 5);
			}
			Nstr nxt;
			nxt["type"] = "right";
			nxt["value"] = nLeftCharacter;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "bg" , 2) == 0){
			dotc(readBuffer);
			nBg = ctos(readBuffer);
			Nstr nxt;
			nxt["type"] = "bg";
			nxt["value"] = nBg;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "dialog" , 6) == 0){
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
				nPerson = "【 " + nPerson + " 】";
			}
			if(nWord.size() != 0){
				nWord = "「 " + nWord + " 」";
			}
			Nstr nxt;
			nxt["type"] = "dialog";
			nxt["person"] = nPerson;
			nxt["word"] = nWord;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
			nPerson.clear();
			nWord.clear();
		}
		else if(strncmp(readBuffer , "click" , 5) == 0){
			Nstr nxt;
			nxt["type"] = "stop";
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "option2" , 7) == 0){
			std::string op1 , op2;
			std::string flag1 , flag2;
			int len = sentense.size();
			int i;
			for(i = 0 ; i < len ; ++ i)
				if(sentense[i] == '"'){
					op1 = getoption(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '|'){
					flag1 = getflag(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '"'){
					op2 = getoption(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '|'){
					flag2 = getflag(sentense , i);
					break;
				}
			Nstr nxt;
			nxt["type"] = "option2";
			nxt["index"] = itos(++ cur);
			nxt["op1"] = op1;
			nxt["op2"] = op2;
			nxt["flag1"] = flag1;
			nxt["flag2"] = flag2;
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "option3" , 7) == 0){
			
		}
		else if(strncmp(readBuffer , "op" , 2) == 0){
			std::string flag = getflag(sentense , 2);
			Nstr nxt;
			nxt["type"] = "flag";
			nxt["index"] = itos(++ cur);
			nxt["value"] = flag;
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 1;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "}" , 1) == 0){
			Nstr nxt;
			nxt["type"] = "}";
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			while(bracket[top - 1] != 1){
				top --;
			}
			top --;
		}
		else if(strncmp(readBuffer , "des" , 3) == 0){
			Nstr nxt;
			nxt["type"] = "des";
			std::string tmp;
			int len = sentense.size();
			for(int i = 5 ; i < len ; ++ i){
				if(sentense[i] == '"') break;
				tmp += sentense[i];
			}
			nxt["value"] = tmp;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
	}
	dfs(init , fd);
	
	char fin[] = "var gao;\n\
var gaoStack = Array();\n\
var gaoCur = 0;\n\
function *dfs(now){\n\
	var flag = false;\n\
	if(now.vis == true){\n\
		\n\
	}\n\
	else if(now.type == \"flag\"){\n\
		if(opFlag[now.value] == undefined || opFlag[now.value] == false){\n\
			//var res = yield now.index;\n\
			flag = true;\n\
		}\n\
	}\n\
	else if(now.type == \"bg\"){\n\
		bgSprite.texture = fromImage(now.value);\n\
	}\n\
	else if(now.type == \"left\"){\n\
		if(now.value == \"clear\") leftCharacterSprite.visible = false;\n\
		else{\n\
			loader.add(now.value).load(function(){\n\
				leftCharacterSprite.visible = true;\n\
				leftCharacterSprite.texture = TextureCache[now.value];\n\
				var source = leftCharacterSprite.texture.baseTexture.source;\n\
			});\n\
		}\n\
	}\n\
	else if(now.type == \"middle\"){\n\
		if(now.value == \"clear\") middleCharacterSprite.visible = false;\n\
		else{\n\
			loader.add(now.value).load(function(){\n\
				middleCharacterSprite.visible = true;\n\
				middleCharacterSprite.texture = TextureCache[now.value];\n\
				var source = middleCharacterSprite.texture.baseTexture.source;\n\
				middleCharacterSprite.x = (game_width - source.width) / 2;\n\
			});\n\
		}\n\
	}\n\
	else if(now.type == \"right\"){\n\
		if(now.value == \"clear\") rightCharacterSprite.visible = false;\n\
		else{\n\
			loader.add(now.value).load(function(){\n\
				rightCharacterSprite.visible = true;\n\
				rightCharacterSprite.texture = TextureCache[now.value];\n\
				var source = rightCharacterSprite.texture.baseTexture.source;\n\
				rightCharacterSprite.x = (game_width - source.width);\n\
			});\n\
		}\n\
	}\n\
	else if(now.type == \"dialog\"){\n\
		person.text = now.person;\n\
				\n\
		word.text = now.word;\n\
	}\n\
	else if(now.type == \"des\"){\n\
		person.text = '';\n\
		\n\
		word.text = now.value;\n\
	}\n\
	else if(now.type == \"stop\"){\n\
		yield now.index;\n\
	}\n\
	else if(now.type == \"option2\"){\n\
		flag1 = now.flag1;\n\
		flag2 = now.flag2;\n\
		option1_text.text = now.op1;\n\
		option2_text.text = now.op2;\n\
		option_visible(true);\n\
	}\n\
	now.vis = true;\n\
	if(!flag){\n\
		for(var nxt = 0 ; nxt < now.sons.length ; ++ nxt){\n\
			gaoStack[gaoCur ++] = yield* dfs(Vtree[now.sons[nxt]]);\n\
		}\n\
	}\n\
}\n\
\n\
gao = dfs(Vtree[1]);\n\
gaoStack[gaoCur ++] = gao;\n\
var vtexture = vsprite.texture.baseTexture;\n\
function onDown(eventData){\n\
	if(option1.visible == true) return;\n\
	if(vtexture.source == null || vtexture.source.ended == true){\n\
		if(person.visible == false){\n\
			person.visible = true;\n\
			word.visible = true;\n\
			graphics.visible = true;\n\
		}\n\
		else{\n\
			while(gaoStack[gaoCur - 1] == undefined) gaoCur --;\n\
			if(gaoCur != 0) gaoStack[gaoCur - 1].next();\n\
		}\n\
	}\n\
}\n\
\n\
function onRight(eventData){\n\
	if(option1.visible == true) return;\n\
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
stage.addChild(middleCharacterSprite);\n\
stage.addChild(rightCharacterSprite);\n\
stage.addChild(graphics);\n\
stage.addChild(person);\n\
stage.addChild(word);\n\
stage.addChild(vsprite);\n\
stage.addChild(clickControl)\n\
stage.addChild(option1);\n\
stage.addChild(option1_text);\n\
stage.addChild(option2);\n\
stage.addChild(option2_text);\n\
stage.addChild(option1Control);\n\
stage.addChild(option2Control);\n\
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
