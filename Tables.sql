create database socialmedia;
use socialmedia;

create table user(
    userid int primary key auto_increment,
    age int not null,
    gender varchar(50) not null,
    urban_rural varchar(50) not null,
    relationship_status varchar(50),
    has_children boolean,
    country varchar(50)
);

create table mentalprofile(
    userid int primary key,
    self_reported_happiness int,
    perceived_stress_score int,
    foreign key (userid) references user(userid)
);

create table healthprofile(
    userid int primary key,
    systolicbp int,
    diastolicbp int,
    body_mass_index int,
    sleep_hours_per_night float,
    diet_quality varchar(50),
    foreign key (userid) references user(userid)
);

create table workprofile(
    userid int primary key,
    income_level varchar(50),
    employment_status varchar(50),
    weekly_work_hours int,
    foreign key (userid) references user(userid)
);

create table lifestyleprofile(
    userid int primary key,
    travel_freq_per_year int,
    books_read_per_year int,
    social_events_per_month int,
    hobbies_count int,
    volunteer_hours_per_month float,
    foreign key (userid) references user(userid)
);

create table education(
    education_id int auto_increment,
    userid int,
    education_level varchar(50) not null,
    foreign key (userid) references user(userid),
    primary key(education_id, userid)
);

create table exercise(
    exerciseid int auto_increment,
    userid int,
    exercise_type varchar(50),
    count int,
    foreign key (userid) references user(userid),
    primary key(exerciseid, userid)
);

create table addiction(
    addictionid int auto_increment,
    userid int,
    addiction_type varchar(50),
    severity_level varchar(50),
    foreign key (userid) references user(userid),
    primary key(addictionid, userid)
);

create table account(
    accountid int auto_increment primary key,
    userid int,
    follows_count int,
    following_count int,
    user_premium boolean,
    account_creation_date date,
    last_login_date date,
    average_session_length float,
    linked_accounts_count int,
    subscription_status varchar(50),
    user_engagement_score float,
    notification_response_rate float,
    preferred_content_theme varchar(50),
    content_type_preference varchar(50),
    sessions_per_day float,
    foreign key (userid) references user(userid)
);

create table securitysettings(
    accountid int primary key,
    two_factor_auth_enabled boolean,
    biometric_login_enabled boolean,
    privacy_setting varchar(50),
    foreign key (accountid) references account(accountid)
);

create table instaactivity(
    activityid int auto_increment,
    userid int,
    posts_created_per_week int,
    reels_watched_per_day int,
    stories_viewed_per_day int,
    likes_given_per_day int,
    comments_made_per_day int,
    time_on_message_per_day int,
    dms_sent_per_week int,
    dms_received_per_week int,
    daily_active_minutes int,
    ads_clicked_per_day int,
    ads_viewed_per_day int,
    time_on_reels_per_day int,
    time_on_explore_per_day int,
    time_on_feed_per_day int,
    foreign key (userid) references user(userid),
    primary key(activityid, userid)
);
