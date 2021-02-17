Level1 = {
    assets = {
        [0] = { type="texture", id = "grasstile-texture", file = "./assets/tilemaps/Grass.png" },
        [1] = { type="texture", id = "swordsman-texture", file = "./assets/images/swordsman/SwordsmanTemplate.png" },
        [2] = { type="texture", id = "orc-texture", file = "./assets/images/Orc/Orc.png" },
        [3] = { type="texture", id = "projectile-texture", file = "./assets/images/projectiles/FireballProjectile.png" },
        [4] = { type="font", id = "thintel-font", file = "./assets/fonts/Thintel.ttf", fontSize = 32 }
    },
    map = {
        textureAssetId = "grasstile-texture",
        file = "./assets/tilemaps/forest.map",
        scale = 3,
        tileSize = 16,
        mapSizeX = 25,
        mapSizeY = 20
    },
    entities = {
        [0] = {
            name = "player",
            layer = 3,
            components = {
                transform = {
                    position = {
                        x = 10,
                        y = 10
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 16,
                    height = 16,
                    scale = 1
                },
                sprite = {
                    textureAssetId = "swordsman-texture",
                    animationInfo = {
                        [0] = {
                            name = "DownIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [1] = {
                            name = "UpIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [2] = {
                            name = "RightIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [3] = {
                            name = "LeftIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [4] = {
                            name = "DownAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [5] = {
                            name = "UpAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [6] = {
                            name = "RightAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [7] = {
                            name = "LeftAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        }

                    },
                    fixed = false
                },
                collider = {
                    tag = "PLAYER",
                    isRendered = false,
                    clampValue = 2,
                },
                input = {
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space"
                    }
                }
            }
        },
        
        [1] = {
            name = "orc",
            layer = 2,
            components = {
                transform = {
                    position = {
                        x = 200,
                        y = 100
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 16,
                    height = 16,
                    scale = 2
                },
                sprite = {
                    textureAssetId = "orc-texture",
                    animationInfo = {
                        [0] = {
                            name = "DownIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [1] = {
                            name = "UpIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [2] = {
                            name = "RightIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [3] = {
                            name = "LeftIdle",
                            frameCount = 1,
                            animationSpeed = 1
                        },
                        [4] = {
                            name = "DownAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [5] = {
                            name = "UpAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [6] = {
                            name = "RightAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        },
                        [7] = {
                            name = "LeftAnimation",
                            frameCount = 4,
                            animationSpeed = 80
                        }

                    },
                    fixed = false
                },
                collider = {
                    tag = "ENEMY",
                    isRendered = false,
                    clampValue = 2,
                },
                projectileEmitter = {
                    textureAssetId =  "projectile-texture",
                    width = 16,
                    height = 16,
                    scale = 0.5,
                    speed = 50,
                    angle = 180,
                    range = 200,
                    shouldLoop = true
                }
            }
        },

        [2] = {
            name = "levelName-text",
            layer = 5,
            components = {
                transform = {
                    position = {
                        x = 0,
                        y = 0
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 16,
                    height = 16,
                    scale = 2
                },
                label ={
                    posX = 10,
                    posY = 10,
                    text = "Level 1",
                    font = "thintel-font"
                }
            }
        }
    } 
}
