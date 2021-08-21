# Minecraft Clone com C++ e SFML

### Criar um diret�rio de desenvolvimento

- Exemplo:

```cmd
	mkdir Game-Projects
```

### Baixar SFML

https://www.sfml-dev.org/

- Descompatar os arquivos dentro do diret�rio de desenvolvimento.

- Renomear a pasta do SFML apenas para `SFML`.


### Criar uma solu��o do Visual Studio

- Criar a solu��o no diret�rio de desenvolvimento onde est� a biblioteca do SFML.

- Criar um projeto C++ vazio.

### Configura��es do Projeto

- Copiar todos os arquivos em `SFML\bin` para a raiz do diret�rio do projeto.

- Clicar em __Projeto__.

- Selecionar a op��o `Propriedades de <Nome do Projeto>`.

- Em `Configura��o` selecionar `Todas as Configura��es`.

- Selecionar a op��o `C++`.

- Selecionar a op��o `Diret�rios de inclus�o Adicionais`.

- Clicar em __Editar__.

- Digitar a linha: `$(SolutionDir)..\SFML\include`.

- Clicar em __OK__.

- Selecionar a op��o `Vinculador`.

- Selecionar a op��o `Diret�rios de biblioteca Adicionais`.

- Clicar em __Editar__.

- Digitar a linha: `$(SolutionDir)..\SFML\lib`.

- Clicar em __OK__.

- Clicar em __Aplicar__.

- Em `Configura��o` alterar para `Release`.

- Selecionar `Vinculador`.

- Selecionar `Entrada`.

- Selecionar `Depend�ncias Adicionais`.

- Clicar em __Editar__.

- Digitar as linhas abaixo:

```cmd
sfml-graphics.lib
sfml-network.lib
sfml-system.lib
sfml-window.lib
sfml-audio.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.

- Clicar em __Aplicar__.

- Em `Configura��o` selecionar `Debug`.

- Selecionar `Vinculador`.

- Selecionar `Entrada`.

- Selecionar `Depend�ncias Adicionais`.

- Clicar em __Editar__.

- Digitar as linhas abaixo:

```cmd
sfml-graphics-d.lib
sfml-network-d.lib
sfml-system-d.lib
sfml-window-d.lib
sfml-audio-d.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.

- Clicar em __Aplicar__.


### Testando com SFML

Ref: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

- Crie um arquivo `main.cpp` em `Arquivos de Origem` e adicione o c�digo a seguir:

```c++
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
```

### Gerando um Execut�vel

- � necess�rio copiar todas as `dll's` dentro de `SFML/bin` para o diret�rio `Debug` e `Release`
- � necess�rio copiar o diret�rio de `resources` para o diret�rio `Debug` e `Release`

#### Criando um icone para o execut�vel.
  
- Precisa ser um arquivo com a extens�o `.ico`.
- Abrir o `Modo de Exibi��o de Recursos` do Visual Studio.
- Clicar com o bot�o direito no nome do projeto em `Modo de Exibi��o de Recursos`.
- Selecionar a op��o __Adicionar__.
- Selecionar a op��o __Recurso__.
- Selecionar a op��o __Icon__.
- Clicar em __Importar__.
- Selecionar o arquivo com a extens�o `.ico`.
- Clicar em __Depurar__.
- Clicar em __Iniciar Depura��o__ para gerar o execut�vel com o icone escolhido.

### Gerando Execut�vel com Link Est�tico

- Clicar em __Projeto__
- Selecionar __Propriedades de __<Nome do Projeto>.__
- Escolher a op��o `Release` ou `Debug` em configura��o.
- Selecionar a op��o `C++`.
- Selecionar a op��o `Pr�-processador`.
- Clicar em `Defini��es do Pr�-processador`.
- Clicar em __Editar__.
- Adicionar a linha `SFML_STATIC`.
- Clicar em __OK__.
- Clicar em __Aplicar__.
- Clicar em __Vinculador__.
- Selecionar `Entrada`.
- Clicar em `Depend�ncias Adicionais`.
- Remover todas as depend�ncias atuais e colocar as depend�ncias abaixo:

```cmd
sfml-graphics-s.lib
sfml-window-s.lib
sfml-system-s.lib
opengl32.lib
freetype.lib	
winmm.lib
gdi32.lib
sfml-audio-s.lib
openal32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
sfml-network-s.lib
ws2_32.lib	
winmm.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.
- Clicar em __Aplicar__.
- Clicar em __OK__.
- Clicar em Iniciar Depura��o.

#### Testando Execut�vel

- Criar uma pasta `Minecraft`.
- Copiar o Execut�vel para dentro da pasta `Minecraft`.
- Copiar a pasta `resources` para dentro da pasta `Minecraft`.
- Copiar o arquivo `openal32.dll` para dentro da pasta `Minecraft`.
- Executar!