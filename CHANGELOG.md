# Changelog

## [1.3.1](https://github.com/jolars/sortedl1/compare/v1.3.0...v1.3.1) (2025-06-11)

### Bug Fixes

* update libslope to v2.8.2 ([c085652](https://github.com/jolars/sortedl1/commit/c085652e4e160a638f29c5a5cb4557f962aaed91))

## [1.3.0](https://github.com/jolars/sortedl1/compare/v1.2.0...v1.3.0) (2025-06-08)

### Features

* update libslope to v2.8.0 ([02a5a1b](https://github.com/jolars/sortedl1/commit/02a5a1b006266996521976e422f0a898e30d8376))

## [1.2.0](https://github.com/jolars/sortedl1/compare/v1.1.1...v1.2.0) (2025-05-30)

### Features

* update libslope to v2.7.0 ([9387915](https://github.com/jolars/sortedl1/commit/93879151b4bbf3dedd7fbdda14b4315baf3c2fd3))

## [1.1.1](https://github.com/jolars/sortedl1/compare/v1.1.0...v1.1.1) (2025-05-30)

### Reverts

* "ci: only trigger release on workflow_dispatch" ([359a31c](https://github.com/jolars/sortedl1/commit/359a31cff06caa05c2b1df6159c6b10d2ab2ac23))

## [1.1.0](https://github.com/jolars/sortedl1/compare/v1.0.1...v1.1.0) (2025-05-27)

### Features

* update libslope to v2.6.0 ([899bfce](https://github.com/jolars/sortedl1/commit/899bfce81bba76964985b7610ed3e01e863e4b73))

### Bug Fixes

* avoid use of `value()` ([5ea72d3](https://github.com/jolars/sortedl1/commit/5ea72d35fb6bc5861a6ce2f193d6681930f5455d))

## [1.0.1](https://github.com/jolars/sortedl1/compare/v1.0.0...v1.0.1) (2025-04-23)

### Bug Fixes

* actually pass `lambda_type` to c++ api ([4903081](https://github.com/jolars/sortedl1/commit/4903081cf9ae20d326ff5403edf4e794552483bf))

## [1.0.0](https://github.com/jolars/sortedl1/compare/v0.7.0...v1.0.0) (2025-04-23)

### ⚠ BREAKING CHANGES

* **path:** allow setting maximum clusters for path method

### Features

* **path:** allow setting maximum clusters for path method ([3eb28c4](https://github.com/jolars/sortedl1/commit/3eb28c4c24a68c768b1eda3ca19bc02d22d1fd1b))

## [0.7.0](https://github.com/jolars/sortedl1/compare/v0.6.0...v0.7.0) (2025-04-23)

### ⚠ BREAKING CHANGES

* change default of `theta1` to 1.0

### Features

* change default of `theta1` to 1.0 ([7eb0930](https://github.com/jolars/sortedl1/commit/7eb09301d8d79662363c9e1a859fe84e6cf44033))
* make lambda type selectable ([f516a3e](https://github.com/jolars/sortedl1/commit/f516a3e20f777d6483d3ccaec492661ce05b60e7))

## [0.6.0](https://github.com/jolars/sortedl1/compare/v0.5.1...v0.6.0) (2025-04-22)

### Features

* enable setting solver via `solver` ([70eb844](https://github.com/jolars/sortedl1/commit/70eb844bcb7f6c02049fb61658db54eecff2464d))

## [0.5.1](https://github.com/jolars/sortedl1/compare/v0.5.0...v0.5.1) (2025-04-22)

### Bug Fixes

* use correct version ([56752f5](https://github.com/jolars/sortedl1/commit/56752f5eda57677384c6d5c0def82ad39f181c03))

## [0.5.0](https://github.com/jolars/sortedl1/compare/v0.4.0...v0.5.0) (2025-04-22)

### Features

* add path early stopping criteria ([a6b690a](https://github.com/jolars/sortedl1/commit/a6b690a144bf4f85f75feeb59da4708eda630ac3))

## [0.4.0](https://github.com/jolars/sortedl1/compare/v0.3.1...v0.4.0) (2025-04-22)

### Features

* add poisson, logistic, multinomial losses ([9858ae7](https://github.com/jolars/sortedl1/commit/9858ae7c0e52ba1f19a543e6343878f7b604aa29))
* enable setting the q parameter ([05734fb](https://github.com/jolars/sortedl1/commit/05734fb15dbb6d97dd8b4339b8460c9bb3adeb96))

## [0.3.1](https://github.com/jolars/sortedl1/compare/v0.3.0...v0.3.1) (2025-04-11)

### Bug Fixes

* don't use `value()` since it does not exist on early macos ([034c9af](https://github.com/jolars/sortedl1/commit/034c9af67982e613eb29c5846bdc87e80055cacb))


### Reverts

* "ci: add pytest to cibuildwheel" ([631f2cb](https://github.com/jolars/sortedl1/commit/631f2cb8f4f3f62c6c48928b6875dc556143c453))
* "ci: update ci workflows: ([6bbfedd](https://github.com/jolars/sortedl1/commit/6bbfedda323ad41c8a3b2ef652c1ce8eb2b6b8ac))

## [0.3.0](https://github.com/jolars/sortedl1/compare/v0.2.3...v0.3.0) (2025-04-10)


### ⚠ BREAKING CHANGES

* change default centering and scaling to `"none"`
* drop support for python 3.7 and 3.8
* deprecate `standardize` in Slope estimator
* change loss value parameterization
* update libslope to v0.21.0
* allow only single float input for `alpha`

### Features

* add slope path ([#31](https://github.com/jolars/sortedl1/issues/31)) ([f407d8c](https://github.com/jolars/sortedl1/commit/f407d8ca628e40484f98481ca0c22d267a3c3ca4))
* allow only single float input for `alpha` ([3f65287](https://github.com/jolars/sortedl1/commit/3f652879e4639535862807416f1e75cabf749a20))
* change default centering and scaling to `"none"` ([7e27318](https://github.com/jolars/sortedl1/commit/7e273184f7b4993fd55187bb80f6e3d8c5c59871))
* change loss value parameterization ([3f65287](https://github.com/jolars/sortedl1/commit/3f652879e4639535862807416f1e75cabf749a20))
* deprecate `standardize` in Slope estimator ([3f65287](https://github.com/jolars/sortedl1/commit/3f652879e4639535862807416f1e75cabf749a20))
* update Eigen to 3.4.0 ([5ce41d2](https://github.com/jolars/sortedl1/commit/5ce41d28d15d0d74c3dd9e3f88bbf6db66cc2604))
* update libslope to v0.21.0 ([3f65287](https://github.com/jolars/sortedl1/commit/3f652879e4639535862807416f1e75cabf749a20))
* update libslope to v0.30.0 ([307f36b](https://github.com/jolars/sortedl1/commit/307f36b06cec7cc3f1edcf9eb79435bff37c7f22))
* update libslope to v0.30.1 ([f012ba6](https://github.com/jolars/sortedl1/commit/f012ba6e08a10e16305485f8f0c3d1b16a8adf11))


### Bug Fixes

* add missing sources to pybind11 module ([a08be2c](https://github.com/jolars/sortedl1/commit/a08be2c64bcf4c8edd3ed67716d8e5828761efba))
* fix convergence issues with solver ([3f65287](https://github.com/jolars/sortedl1/commit/3f652879e4639535862807416f1e75cabf749a20))


### Dependencies

* cet scikit-build-core minversion to 0.10 and remove cmake ver ([bd63a29](https://github.com/jolars/sortedl1/commit/bd63a29addd530f31e49a3943f55bdb2220019c2))
* drop support for python 3.7 and 3.8 ([139e0d8](https://github.com/jolars/sortedl1/commit/139e0d837d6177ebfca95ed6dc2d8df6673cf136))


### Documentation

* document as compliantwith python 3.13 ([87e9219](https://github.com/jolars/sortedl1/commit/87e9219917bc69b9b4c01e3fdea630abc1d49e77))
* update copyright year ([cd707c4](https://github.com/jolars/sortedl1/commit/cd707c4097c0124de7d22559c4a514ad34c38861))

## [0.2.3](https://github.com/jolars/sortedl1/compare/v0.2.2...v0.2.3) (2024-02-07)


### Bug Fixes

* **deps:** update to libslope 0.3.1 ([bac6f93](https://github.com/jolars/sortedl1/commit/bac6f93a2dcb0e3ab4cfbe8beb174ede34e6838b))
* update libslope to 0.3.2 ([c059f6a](https://github.com/jolars/sortedl1/commit/c059f6a4d584827e9410f6d715aa3eb4a2b18728))


### Documentation

* make logo work better for mobile phones ([765077a](https://github.com/jolars/sortedl1/commit/765077a77c6082e36aa3b288e564ae9bdece5c1d))

## [0.2.2](https://github.com/jolars/sortedl1/compare/v0.2.1...v0.2.2) (2023-12-14)


### Reverts

* "ci: build documentation once through ci to have something on the page" ([118a416](https://github.com/jolars/sortedl1/commit/118a4163532ed785bf263cecb108db1bff84a61c))


### Documentation

* add changelog to docs ([defdaae](https://github.com/jolars/sortedl1/commit/defdaae7c4eab97fb505d6cb7f06161fdf957459))
* add codecov badge to readme ([7ac3148](https://github.com/jolars/sortedl1/commit/7ac3148256784894318e6942be9d62e48d1d71c3))
* add file-level docstring from estimators.py ([fa98821](https://github.com/jolars/sortedl1/commit/fa98821970d20b1bdf9f911c01e8128e1738e71f))
* add logos and fix duplicate documentation ([50b29eb](https://github.com/jolars/sortedl1/commit/50b29eb44ffb2a51f23762582d6913f1ca872181))
* add source code link in docs ([4b61204](https://github.com/jolars/sortedl1/commit/4b61204777a714a20b59e68de3ad362085623f72))
* don't use sphinx-apidoc ([4c168ac](https://github.com/jolars/sortedl1/commit/4c168ac42fa1c2a182bccfb4ddfa019baee6aa10))
* fix autosummary documentation ([87d5cf3](https://github.com/jolars/sortedl1/commit/87d5cf3e0989362858a4860686ed446bc46afe4c))
* fix SLOPE -&gt; sortedl1, and write about convcommits ([15c1166](https://github.com/jolars/sortedl1/commit/15c1166a750612fd2cfbe75ee3bc6ed9c0db5d52))
* fix typo and pip instructions ([4e78858](https://github.com/jolars/sortedl1/commit/4e78858db7c23d2e2a59eeb4afc025a2eac929c2))
* specify main branch for badge in readme ([abdc18e](https://github.com/jolars/sortedl1/commit/abdc18ec1266a24f4cd4ec2e954d6f7b1348762f))
* update logo ([7ad646c](https://github.com/jolars/sortedl1/commit/7ad646c42aaf8ea7a5d1f7e579e0c6724b02dab2))
* update readme with badges and pypi info ([c3edd6e](https://github.com/jolars/sortedl1/commit/c3edd6eaa0d786f8c920a5a21f0ba84083782124))
* use ivar for napoleon ([c6d8522](https://github.com/jolars/sortedl1/commit/c6d85222fb4e032547a13f674db3f342999d9800))
* use myst parser ([0288739](https://github.com/jolars/sortedl1/commit/0288739f1d40ec9b9370da3d029bce9829fdf162))

## [0.2.1](https://github.com/jolars/sortedl1/compare/v0.2.0...v0.2.1) (2023-12-11)


### Documentation

* add authors to sphinx docs too ([db8bc88](https://github.com/jolars/sortedl1/commit/db8bc8860ca25abefea368ed60311a8bcb72c006))
* document all authors ([7124713](https://github.com/jolars/sortedl1/commit/7124713dad90fb0a21692e829f238a08c5baada6))
* fix keyword ([1597d21](https://github.com/jolars/sortedl1/commit/1597d214973174c951f7f4c9cb9ee746e370a6a2))

## [0.2.0](https://github.com/jolars/sortedl1/compare/v0.1.0...v0.2.0) (2023-12-11)


### Features

* add max_iter and tol parameters to Slope ([46ec82d](https://github.com/jolars/sortedl1/commit/46ec82dcad40ea58ef8a6023b9d77d2f63a7f14d))
* make estimator fully scikit-learn compliant (and test it) ([0e236fe](https://github.com/jolars/sortedl1/commit/0e236fe6d529a6dc9018fbc3b506c9e15c619a57))
* support sparse X input ([8d2cf08](https://github.com/jolars/sortedl1/commit/8d2cf082d6c9213cfc25d188aea31158e05a2453))
* support standardization and intercept ([99f9aee](https://github.com/jolars/sortedl1/commit/99f9aee4edebb6e0865bef334cbce91325b6d7f6))
* update to libslope 0.2.0 ([f5ecaad](https://github.com/jolars/sortedl1/commit/f5ecaad85154a4343ce3eb6c72b8e60a748de972))


### Bug Fixes

* return intercept as float ([5e83de1](https://github.com/jolars/sortedl1/commit/5e83de13049509db2d85f6b0cd8f6515ff4ae5fb))
* update to libslope 0.3.0 ([905424f](https://github.com/jolars/sortedl1/commit/905424f1786277cf19f7d81b3de847f7b107d04b))


### Documentation

* add a few more classifiers ([42ad653](https://github.com/jolars/sortedl1/commit/42ad653fb85d175feb3b4c3bf156bcc179d6cafa))
* add docstring for module ([7294370](https://github.com/jolars/sortedl1/commit/72943702eac8e324de0a6f7ddca8d1bf01e26a3b))
* add some additional classifiers ([e649ffd](https://github.com/jolars/sortedl1/commit/e649ffd5d7054d9ecf4581c6e04ee4e74153b6f6))
* add some additional files for pyproject.toml ([a9ea635](https://github.com/jolars/sortedl1/commit/a9ea63536b94da2852a4c657b7abc7658237aed0))
* add some basic information on readme ([8f4c4e0](https://github.com/jolars/sortedl1/commit/8f4c4e026a6336ae1a0dfda646137361a38ccb16))
* clean up documentation and add copybutton ([4e51a29](https://github.com/jolars/sortedl1/commit/4e51a29fb3c433320fc420e9a17bf7aceb6c479c))
* document att attributes ([4b881f2](https://github.com/jolars/sortedl1/commit/4b881f234e7995640351be78f3d61eb6d410f672))
* document tests ([027a2da](https://github.com/jolars/sortedl1/commit/027a2da6b8ca3b2f22788dffdf0617992e6f5ad8))
* don't say what defaults are in documentation ([8fa20cd](https://github.com/jolars/sortedl1/commit/8fa20cd81c6f6017899a647f8bf1126c9e5d28ee))
* fix documentation for slope ([1069aff](https://github.com/jolars/sortedl1/commit/1069afff8d637ffec09abb88a8078ca08d6aabad))
* fix linting error for estimators.py ([eba539b](https://github.com/jolars/sortedl1/commit/eba539bcfab03f2a227bcc7462fcc5b5457dc40f))
* fix sorting of python version ([9ef1433](https://github.com/jolars/sortedl1/commit/9ef143317fab6d30b16aa1da3bf00a9703f7cbd9))
* increment header in readme ([b94c9b1](https://github.com/jolars/sortedl1/commit/b94c9b1f540e03908433a56b5c0a8b605634d54b))
* polish readme a bit ([4cceb1b](https://github.com/jolars/sortedl1/commit/4cceb1bc60d4d065faa09fdde1e337940db3edba))
* switch to furo theme ([6006fd9](https://github.com/jolars/sortedl1/commit/6006fd9b8c8dba51ab5e20d02a1ee242bb9a5413))
* update authors and make version dynamic ([a29a16b](https://github.com/jolars/sortedl1/commit/a29a16b7dbb3985036d3e005618b76cc21f13356))
* use static version instead ([6071f9d](https://github.com/jolars/sortedl1/commit/6071f9dc740198d7f73269d0b73159d04f2f10bb))

## 0.1.0 (2023-11-30)


### Features

* add a docs workflow ([7981b47](https://github.com/jolars/sortedl1/commit/7981b4784658ae420ded8149820a77f620b8f009))
* add basic package infrastructure ([e53a245](https://github.com/jolars/sortedl1/commit/e53a245b9dfcd02b95bc43e20afc31e2c4f4e8bd))
* add initial c++ source for libslope ([a118ed4](https://github.com/jolars/sortedl1/commit/a118ed4d73c1c3b990c37d8943765cbee8600c5b))
* add requirements to extras for building documentation ([a5362bc](https://github.com/jolars/sortedl1/commit/a5362bc4f2ef8d631c01bcc5a9c8de13f9fa06e2))
* change to sklearn-compatible interface ([41d4836](https://github.com/jolars/sortedl1/commit/41d4836db48f0639b2fbcff19f96caab76650c03))
* make cpp function return a tuple with actual estimates ([3c3ff24](https://github.com/jolars/sortedl1/commit/3c3ff249813b09ac101f8c8c5647b588c58e2e53))


### Bug Fixes

* fix test to work with new api ([3192911](https://github.com/jolars/sortedl1/commit/31929115fb16cbf34df4c08d2a652555bd156f9e))
* move installation dependencies to setup.py ([2506902](https://github.com/jolars/sortedl1/commit/2506902e4ff7197646be9e284dafe589371e3c0b))
* use scikit-learn, not sklearn, as dependency ([dc78b49](https://github.com/jolars/sortedl1/commit/dc78b493de03d28561aa1fac63f1f0a594ce7a02))


### Documentation

* add initial docs ([b4a5bac](https://github.com/jolars/sortedl1/commit/b4a5bac42f4f8fad093348ee568b363ed4f49516))
* change estimators to models ([24c57ec](https://github.com/jolars/sortedl1/commit/24c57ecc24a4d6cc9d42093bcbcc171a3f175f97))
* change to sphinx build/source structure ([ed9ab31](https://github.com/jolars/sortedl1/commit/ed9ab31f309c55db72e0a4e1721b0edf12f8031f))
* remove documentation stubs from cpp file ([69bf98c](https://github.com/jolars/sortedl1/commit/69bf98cac8a676d7d9c3441663705ff88bb3b9eb))
* run apidoc for correct location ([4246e41](https://github.com/jolars/sortedl1/commit/4246e414ce6219e8671c0f74f485c5d17967bbe3))
