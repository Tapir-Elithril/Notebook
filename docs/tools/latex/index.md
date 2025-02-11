# LaTeX
## 工具
Texlive
```
sudo apt install texlive-full
```
Mathtype固定公式转化为LaTeX  
Mathpix手写公式、计算机生成公式转化为LaTeX  
Vscode插件：  

- latex workshop
- latex utilities
- Ctrl + Shift + P -> Preferences: Open Settings (JSON) -> settings.json  
  
```
"latex-workshop.latex.recipes": [
  {
    "name": "pdflatex",
    "tools": ["pdflatex"]
  },
  {
    "name": "latexmk",
    "tools": ["latexmk"]
  }
],
"latex-workshop.latex.tools": [
  {
    "name": "pdflatex",
    "command": "pdflatex",
    "args": ["-interaction=nonstopmode", "-synctex=1", "%DOC%"]
  },
  {
    "name": "latexmk",
    "command": "latexmk",
    "args": ["-pdf", "-interaction=nonstopmode", "-synctex=1", "%DOC%"]
  }
],
"latex-workshop.view.pdf.viewer": "tab",
"latex-workshop.latex.autoBuild.run": "onFileChange"
```

参考 BV1LT4y1y7oz