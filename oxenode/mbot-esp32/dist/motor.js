var r={d:(e,t)=>{for(var n in t)r.o(t,n)&&!r.o(e,n)&&Object.defineProperty(e,n,{enumerable:!0,get:t[n]})},o:(r,e)=>Object.prototype.hasOwnProperty.call(r,e)},e={};r.d(e,{VG:()=>c,xz:()=>l,ZP:()=>u,Tt:()=>p});const t=window.OxenodeCore,n=window.OxenodeUi,o=window.jsxRuntimeExports;function a(r){return function(r){if(Array.isArray(r))return i(r)}(r)||function(r){if("undefined"!=typeof Symbol&&null!=r[Symbol.iterator]||null!=r["@@iterator"])return Array.from(r)}(r)||function(r,e){if(!r)return;if("string"==typeof r)return i(r,e);var t=Object.prototype.toString.call(r).slice(8,-1);"Object"===t&&r.constructor&&(t=r.constructor.name);if("Map"===t||"Set"===t)return Array.from(r);if("Arguments"===t||/^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(t))return i(r,e)}(r)||function(){throw new TypeError("Invalid attempt to spread non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.")}()}function i(r,e){(null==e||e>r.length)&&(e=r.length);for(var t=0,n=new Array(e);t<e;t++)n[t]=r[t];return n}function s(r,e,t,n,o,a,i){try{var s=r[a](i),c=s.value}catch(r){return void t(r)}s.done?e(c):Promise.resolve(c).then(n,o)}var c="Motor";function u(r){var e=r.node;return(0,o.jsxs)(o.Fragment,{children:[(0,o.jsx)("h3",{children:"Motor"}),(0,o.jsx)("span",{className:"xsmall",children:"Control motors"}),(0,o.jsxs)(n.Select,{nodeId:e.id,name:"mode",value:"1",children:[(0,o.jsx)("option",{value:"1",children:"Go Forward"}),(0,o.jsx)("option",{value:"2",children:"Turn Left"}),(0,o.jsx)("option",{value:"3",children:"Turn Right"}),(0,o.jsx)("option",{value:"4",children:"Brake"})]}),(0,o.jsx)(n.NumberInput,{nodeId:e.id,name:"speed",value:"50"}),e.State.err&&(0,o.jsx)(o.Fragment,{children:(0,o.jsx)("span",{style:{margin:"0.25rem",color:"var(--red)"},children:e.State.err})})]})}function l(r){return d.apply(this,arguments)}function d(){var r;return r=function*(r){var e,t,n=r.node,o=r.controller,i=r.inputs.socket,s=r.state,c=s.mode,u=s.speed;switch(c){case"1":e=new Uint8Array([u]),t=new Uint8Array([u]);break;case"2":e=new Uint8Array([-u]),t=new Uint8Array([u]);break;case"3":e=new Uint8Array([u]),t=new Uint8Array([-u]);break;case"4":e=new Uint8Array([0]),t=new Uint8Array([0])}var l=new Uint8Array([192].concat(a(e),a(t)));if(console.log(l),!i)return n.State.err="Socket is not connected...",o.update(n),o.trigger(0);i.send(l);var d=yield new Promise((function(r){i.onmessage=function(e){r(e)}}));return console.log(d),o.trigger(0)},d=function(){var e=this,t=arguments;return new Promise((function(n,o){var a=r.apply(e,t);function i(r){s(a,n,o,i,c,"next",r)}function c(r){s(a,n,o,i,c,"throw",r)}i(void 0)}))},d.apply(this,arguments)}var p=[t.port.input().type("trigger"),t.port.input().type("data").label("socket"),t.port.output().type("trigger")],y=e.VG,f=e.xz,m=e.ZP,v=e.Tt;export{y as Name,f as Trigger,m as default,v as ports};