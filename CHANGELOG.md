# Changelog

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
